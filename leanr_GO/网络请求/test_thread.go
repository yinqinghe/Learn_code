package main

import (
	"crypto/tls"
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
	"strconv"
	"strings"
	"sync"
	"time"
	// "golang.org/x/text/encoding/simplifiedchinese"
)

const (
	routineCountTotal = 20 //限制线程数
)

var proxyUrl, _ = url.Parse("http://127.0.0.1:8080")

var transport = &http.Transport{
	Proxy: http.ProxyURL(proxyUrl), //设置代理发送请求
	TLSClientConfig: &tls.Config{
		InsecureSkipVerify: true, //通过设置Transport的TLSClientConfig来忽略证书验证:
	},
}

var client = http.Client{
	Timeout:   time.Second * 10,
	Transport: transport,
}

func main() {
	file_path := "D:\\Downloads\\tmp\\nps.txt"
	data, err := ioutil.ReadFile(file_path)
	if err != nil {
		fmt.Println(err)
		return
	}
	lines := strings.SplitAfter(string(data), "\r\n")

	beg := time.Now()
	wg := &sync.WaitGroup{}
	tasks := make(chan [2]string)
	results := make(chan string)
	//receiver接受响应并处理的函数块, 也可以单独写在一个函数
	//go func() {
	//	for result := range results {
	//		if result == "" {
	//			close(results)
	//		} else {
	//			fmt.Println("result:", result)
	//		}
	//	}
	//}()
	for i := 0; i < routineCountTotal; i++ {
		wg.Add(1)
		go worker(wg, tasks, results)
	}
	start := 0
	end := 10
	// end := len(lines)
	//分发任务
	for i, task := range lines[start:end] {
		lineNo := i + start + 1

		tasks <- [2]string{task, strconv.Itoa(lineNo)}
	}
	tasks <- [2]string{} //worker结束标志
	wg.Wait()            //同步结束
	results <- ""        // result结束标志
	fmt.Printf("time consumed: %fs", time.Now().Sub(beg).Seconds())
}

func worker(group *sync.WaitGroup, tasks chan [2]string, result chan string) {
	for task := range tasks {
		if len(task) == 0 { //如果task为空  则关闭taskts
			close(tasks)
		} else {
			NumberQueryRequest(task)
		}
	}
	group.Done()
}

func NumberQueryRequest(t [2]string) {
	// url := ip_
	url := "https://www.baidu.com/"
	// 创建一个 HTTP 请求
	req, err := http.NewRequest("GET", url, nil)
	// resp, err := client.Get(url)
	if err != nil {
		return
	}
	req.Header.Add("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36")
	resp, err := client.Do(req)
	if err != nil {
		fmt.Println("发送请求失败:", err)
		return
	}
	// defer req.Body.Close()
	// body, err := ioutil.ReadAll(req.Body)
	// if err != nil {
	// 	return
	// }

	// 发送请求
	if resp.StatusCode == 200 {
		println("响应码为：", resp.StatusCode)
	}
	fmt.Println(resp.StatusCode)

}
