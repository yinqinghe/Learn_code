package main

import (
	"crypto/cipher"
	"crypto/des"
	"fmt"
)

func main() {
	datass := "7f5b10f36d6a65e363caa56d6187801953c0ec97717a93bf4a147ec2a71b4e36468621e4436a9e31bac9b571058b788e408623e77c6b726a256963e6d3e4b9d5256963e6d3e4b9d5256963e6d3e4b9d51821404d558a611d610c77b9037c84e21821404d558a611dd85345102587cef41ff62cec8fe62ae1610c77b9037c84e2724075dde24450ba63caa56d61878019364485aabb8af321eed991779543c2275450c05f7d0ab32c63caa56d618780194cb25868e27a485d1ff62cec8fe62ae1b99f68fc3b2e52e963caa56d618780194cb25868e27a485d1ff62cec8fe62ae1aa5f3867ce69032a63caa56d618780194cb25868e27a485d1ff62cec8fe62ae160c66e84e69472b463caa56d618780194cb25868e27a485d27b04da649ba9196d85345102587cef463caa56d618780193be7bcd94c23f4f509e04bbaf2a35cd34dbd5531c66f74214dbd5531c66f742131f4aabd04676088364485aabb8af32165429d5bdfecffbe63caa56d61878019364485aabb8af32189ac760f62f68869e25b97ee66fb18ff20d39635334c81cb6efc283107502480581ea8f4b255edb6a7f7a433e9255ea51333f0be111c2e7a60c66e84e69472b41821404d558a611d836e7e981b18c4ff65429d5bdfecffbea7b2844e90a503681821404d558a611db83d4bfb6ae764b0836e7e981b18c4ff9b5565c406ecdd2e26dedde26c4ab7ca1ff62cec8fe62ae11821404d558a611d610c77b9037c84e263caa56d618780194cb25868e27a485d1ff62cec8fe62ae160c66e84e69472b44cb25868e27a485d8d608f749728f25820d39635334c81cb63caa56d61878019b83d4bfb6ae764b03263755c1f65815c4b22e562b2fa176dc9a094f038552bf2035915d4db1f57fcaa5f3867ce69032a74ee913195affdf6a7f7a433e9255ea57f8a6043d4b2b93a27b04da649ba91964cb25868e27a485d839774cf8c545ff21ce4bbd7357ee8ed256963e6d3e4b9d5256963e6d3e4b9d5256963e6d3e4b9d563caa56d618780196dc75537007e4a5e89ac760f62f68869a7eae65137ce3edbefd098bc4b6850d663caa56d61878019b83d4bfb6ae764b03263755c1f65815cd85345102587cef44cb25868e27a485d63caa56d61878019aa5f3867ce69032a804c11813d6c3c164cb25868e27a485d27c7b0bf0bab021c60c66e84e69472b4ea006f751ef6cdfeb83d4bfb6ae764b03263755c1f65815c98a4281bfd7d9843724075dde24450ba63caa56d61878019f095ffeeeed6350b65429d5bdfecffbe1821404d558a611d4cb25868e27a485dc8b4eba8bbdf55c61ce4bbd7357ee8ed63caa56d61878019b83d4bfb6ae764b06e0733deae77b07131f4aabd04676088364485aabb8af32165429d5bdfecffbe63caa56d61878019364485aabb8af32189ac760f62f68869e25b97ee66fb18ff1821404d558a611d836e7e981b18c4ff65429d5bdfecffbea7b2844e90a503681821404d558a611db83d4bfb6ae764b0836e7e981b18c4ff9b7ed87155fd8b2f5785ca0d87972ae07f8a6043d4b2b93a04bc48faaf93c1dc36f6b38b03498e8e47ba1d4493d7465736f6b38b03498e8e7749d5c182e680aa177d8ac3c8adfb8d8435928365cd5f84c938ce808bea66557e730bdb13319ae27f8a6043d4b2b93a979fb166904c341cd10e5110f6228c05804c11813d6c3c164cb25868e27a485d27c7b0bf0bab021c7749d5c182e680aaea006f751ef6cdfeb83d4bfb6ae764b03263755c1f65815c4b22e562b2fa176d1821404d558a611d4cb25868e27a485d65350e2c031e292763caa56d61878019804c11813d6c3c164cb25868e27a485d27c7b0bf0bab021c4100ba70381d5d15ea006f751ef6cdfeb83d4bfb6ae764b03263755c1f65815c1821404d558a611d4cb25868e27a485dc716670be75e73aa1ce4bbd7357ee8ed63caa56d61878019b83d4bfb6ae764b03263755c1f65815c1821404d558a611dd10e5110f6228c051821404d558a611dd10e5110f6228c05169cdabeb7cabd09f6576b9f51187623ab27741c656341631821404d558a611dd10e5110f6228c051821404d558a611df6576b9f511876231821404d558a611dab27741c6563416363caa56d6187801953c0ec97717a93bff0dfd8d3f0b0fd4460c66e84e69472b41821404d558a611d1ff62cec8fe62ae1f095ffeeeed6350b5785ca0d87972ae0d10e5110f6228c051821404d558a611df6576b9f51187623ab27741c6563416363caa56d618780194cb25868e27a485da0607e2a5ad52b169e963403797b052069d4f367b6912e74f095ffeeeed6350bf095ffeeeed6350bf095ffeeeed6350b094b953e2c4acf9a2d5dd3bd1ee232e9256963e6d3e4b9d5ea006f751ef6cdfe300a240d2cc8fa727dd8573dad3cc551abd1b68e6f042b3a16a21199f9928892abd1b68e6f042b3a16a21199f99288925450c05f7d0ab32ca7eae65137ce3edb256963e6d3e4b9d51821404d558a611d724075dde24450baea006f751ef6cdfe281ca13e4a9fbb7dc7335b005a04adac36f6b38b03498e8e281ca13e4a9fbb7d04bc48faaf93c1dc1821404d558a611d16b71cf09c4f9f6536f6b38b03498e8e7dd8573dad3cc551e40e8af09a624328a0bf296532203924f095ffeeeed6350ba4fc7e1d9bf7c53263caa56d61878019364485aabb8af32165429d5bdfecffbe63caa56d61878019364485aabb8af321eed991779543c22731f4aabd04676088364485aabb8af32189ac760f62f6886931f4aabd04676088364485aabb8af32165429d5bdfecffbe1821404d558a611dd85345102587cef41821404d558a611dd85345102587cef41821404d558a611d16b71cf09c4f9f65308b3943c6b7c468724075dde24450ba28ad276dc725336db18d95267e9d4f08f095ffeeeed6350ba4fc7e1d9bf7c53225ce8d8c02024c696c9e5b466b56da46ab27741c6563416363caa56d61878019281ca13e4a9fbb7d836e7e981b18c4ff1821404d558a611ddf31fa5d63b1044ed85345102587cef4256963e6d3e4b9d5256963e6d3e4b9d5256963e6d3e4b9d531f4aabd04676088364485aabb8af32165429d5bdfecffbe1821404d558a611d610c77b9037c84e21821404d558a611d610c77b9037c84e22d5dd3bd1ee232e947ba1d4493d746571821404d558a611d610c77b9037c84e21821404d558a611d16b71cf09c4f9f6571b2830b645b5819281ca13e4a9fbb7db6ffbdc24fb38e92ebab018953d2a882f095ffeeeed6350ba4fc7e1d9bf7c53225ce8d8c02024c69f6576b9f511876231fcb5ab9a452b9cb63caa56d61878019281ca13e4a9fbb7d836e7e981b18c4ff63caa56d61878019364485aabb8af321eed991779543c227ea006f751ef6cdfe281ca13e4a9fbb7d979fb166904c341c31f4aabd04676088364485aabb8af32165429d5bdfecffbe1ff62cec8fe62ae103a29b360a3e9334256963e6d3e4b9d5a7f7a433e9255ea527c7b0bf0bab021ca58f2deae885033e1ff62cec8fe62ae11ff62cec8fe62ae11821404d558a611d16b71cf09c4f9f6525ce8d8c02024c69442e5bccb1ba8f902e2e75cef1d17acdc6b2906b48ff685af095ffeeeed6350ba4fc7e1d9bf7c53263caa56d61878019281ca13e4a9fbb7debab018953d2a88263caa56d6187801953c0ec97717a93bfeaea1d27ed7f24f5d85345102587cef42d5dd3bd1ee232e9970b7ccb6db4a3721199bb4e068e819e63caa56d61878019281ca13e4a9fbb7d04bc48faaf93c1dc63caa56d61878019281ca13e4a9fbb7d33668886491f3655ea006f751ef6cdfe2acd7628ca83468b89ac760f62f68869f095ffeeeed6350bf095ffeeeed6350bf095ffeeeed6350bf095ffeeeed6350b31f4aabd04676088364485aabb8af32165429d5bdfecffbe1ff62cec8fe62ae11ff62cec8fe62ae11821404d558a611d16b71cf09c4f9f65cdbf9196ff295c000ec6170bffd88d0caa5f3867ce69032a2491a02f1c620db4f095ffeeeed6350ba4fc7e1d9bf7c5326dc75537007e4a5e89ac760f62f688693be7bcd94c23f4f56dc75537007e4a5e26611fc5ec5c6bc6b83d4bfb6ae764b0256963e6d3e4b9d5256963e6d3e4b9d563caa56d61878019f095ffeeeed6350b0aaeea56164d69603be7bcd94c23f4f5a58f2deae885033ee30ce52ce7697604b83d4bfb6ae764b0256963e6d3e4b9d5256963e6d3e4b9d525ce8d8c02024c69da846df940582d399e963403797b05204a147ec2a71b4e36b83d4bfb6ae764b0256963e6d3e4b9d5256963e6d3e4b9d5bac9b571058b788eb23ec550d6695990f095ffeeeed6350bf095ffeeeed6350bf095ffeeeed6350bd41b218cdb3bf2092d5dd3bd1ee232e930af7b354af45c007f8a6043d4b2b93a5450c05f7d0ab32c27b04da649ba919628ad276dc725336dcdbf9196ff295c00f583aa02d899c2382e2e75cef1d17acdf583aa02d899c2382e2e75cef1d17acda8579fafe9f94a902e2e75cef1d17acd6c9e5b466b56da46d55be5e290d9b221abd1b68e6f042b3a8a965b72e387c8cf2e2e75cef1d17acd8a965b72e387c8cfabd1b68e6f042b3a16a21199f99288922e2e75cef1d17acd2d5dd3bd1ee232e96c9e5b466b56da46256963e6d3e4b9d5701ae34d4113f138e30ce52ce769760405943569127c92f66dc75537007e4a5ecef398e411e3ffdd16b71cf09c4f9f651333f0be111c2e7aea006f751ef6cdfe7d4aab5071d9aceb25d7e833c47dacc75fbb9b7b4ec8634a1d4a5c243305bd5089f6ba2d44b45ae7804c11813d6c3c16e50a1dc8cd0046a6155652a810094f949f3cd2724c18fbfaa7eae65137ce3edbb18d95267e9d4f089f3cd2724c18fbfa1ce4bbd7357ee8edb3f8e1411400e907c557eb0731a9f5d5147f2afacae33fe9abd1b68e6f042b3a18d642ac9616356f65429d5bdfecffbe35b33558bde8b2b55fbb9b7b4ec8634a7d4aab5071d9aceb147f2afacae33fe9724075dde24450bac6b2906b48ff685ad85345102587cef413694596067b9a48fbb730c21f9ed8bba7eae65137ce3edbf49befe25c8c74e803a29b360a3e93349eda9995d15ae5b231f4aabd04676088f583aa02d899c2387b3cfa2d9892006df24ea9aebbe44dc180b1ae1555981db89b69c8a4a42a06934ea16d25f0550d3669d4f367b6912e743acd751330e188836e0733deae77b0715fbb9b7b4ec8634a6c9e5b466b56da469e963403797b0520256963e6d3e4b9d51821404d558a611db41a8950adc4000fb41a8950adc4000f5450c05f7d0ab32c997f09a21620631da7eae65137ce3edb308b3943c6b7c46860c66e84e69472b4a7eae65137ce3edb5450c05f7d0ab32c035915d4db1f57fca7eae65137ce3edbd41b218cdb3bf20903a29b360a3e9334a7eae65137ce3edb8a965b72e387c8cfd55be5e290d9b2211333f0be111c2e7a6efc283107502480997f09a21620631d997f09a21620631dd55be5e290d9b221abd1b68e6f042b3ab41a8950adc4000f6efc283107502480a7eae65137ce3edbabd1b68e6f042b3adced51ab49cbee0b16a21199f9928892d41b218cdb3bf209035915d4db1f57fc03a29b360a3e9334a7eae65137ce3edb8a965b72e387c8cfd55be5e290d9b22113082609b84d50dd035915d4db1f57fc8a965b72e387c8cfd55be5e290d9b2211333f0be111c2e7a6efc283107502480997f09a21620631d997f09a21620631dd55be5e290d9b221abd1b68e6f042b3ab41a8950adc4000f6efc283107502480a7eae65137ce3edbabd1b68e6f042b3adced51ab49cbee0b16a21199f9928892d41b218cdb3bf209035915d4db1f57fc8a965b72e387c8cfd55be5e290d9b221c6b2906b48ff685a30af7b354af45c004423d01b009c9490e5a0425cd14a748f2e2e75cef1d17acdc938ce808bea66551333f0be111c2e7a46a7ac8fb86c1768d41b218cdb3bf20946a7ac8fb86c1768c6b2906b48ff685a30af7b354af45c004423d01b009c9490e5a0425cd14a748f2e2e75cef1d17acd9b7ed87155fd8b2fa7b2844e90a50368970b7ccb6db4a3721821404d558a611db41a8950adc4000fb41a8950adc4000f5450c05f7d0ab32c997f09a21620631da7eae65137ce3edbcdbf9196ff295c0036f6b38b03498e8e6efc28310750248016a21199f9928892efd098bc4b6850d67f8a6043d4b2b93a6efc283107502480efd098bc4b6850d65450c05f7d0ab32c308b3943c6b7c46860c66e84e69472b45450c05f7d0ab32c16a21199f9928892cdbf9196ff295c00442e5bccb1ba8f909d2cd96b73bc76f11333f0be111c2e7a5450c05f7d0ab32c16a21199f9928892c6b2906b48ff685a30af7b354af45c004423d01b009c9490e5a0425cd14a748f2e2e75cef1d17acd99cf9b5369eda715a7b2844e90a50368970b7ccb6db4a3721ff62cec8fe62ae15450c05f7d0ab32c4b22e562b2fa176d5450c05f7d0ab32c27b04da649ba91965450c05f7d0ab32c27b04da649ba9196308b3943c6b7c46860c66e84e69472b403a29b360a3e9334a7eae65137ce3edba7eae65137ce3edb997f09a21620631d308b3943c6b7c468d41b218cdb3bf209d41b218cdb3bf209b41a8950adc4000fdced51ab49cbee0b82ff03e99406fb515450c05f7d0ab32c2e2e75cef1d17acd2d5dd3bd1ee232e930af7b354af45c007f8a6043d4b2b93a5450c05f7d0ab32c27b04da649ba919628ad276dc725336d2e2e75cef1d17acdb41a8950adc4000fdced51ab49cbee0b8a965b72e387c8cfd41b218cdb3bf209a7b2844e90a50368970b7ccb6db4a3721821404d558a611db41a8950adc4000fb41a8950adc4000f5450c05f7d0ab32c997f09a21620631da7eae65137ce3edbcdbf9196ff295c008435928365cd5f8416a21199f9928892b41a8950adc4000fdced51ab49cbee0b82ff03e99406fb51abd1b68e6f042b3a16a21199f9928892efd098bc4b6850d6308b3943c6b7c46860c66e84e69472b4efd098bc4b6850d6293dc18dab1d0d8dabd1b68e6f042b3a997f09a21620631d1333f0be111c2e7a60c66e84e69472b482ff03e99406fb515450c05f7d0ab32c4b22e562b2fa176dd55be5e290d9b2216efc283107502480a7eae65137ce3edb5450c05f7d0ab32ca7b2844e90a50368970b7ccb6db4a372442e5bccb1ba8f906c9e5b466b56da465450c05f7d0ab32c27b04da649ba9196cdbf9196ff295c001821404d558a611defd098bc4b6850d65450c05f7d0ab32c16a21199f9928892a7eae65137ce3edb308b3943c6b7c46860c66e84e69472b431f4aabd04676088dced51ab49cbee0b293dc18dab1d0d8dabd1b68e6f042b3ad55be5e290d9b221d55be5e290d9b2216efc283107502480d41b218cdb3bf20999cf9b5369eda7152e2e75cef1d17acde5a0425cd14a748f60c66e84e69472b48a4d3ec7438d32fb71b2830b645b5819abd1b68e6f042b3a16a21199f992889282ff03e99406fb51dced51ab49cbee0b7dd8573dad3cc5516c9e5b466b56da4660c66e84e69472b4ada97489907123c282f3271f3d0df41960c66e84e69472b4357001074f4d24a12e2e75cef1d17acdf583aa02d899c238c6b2906b48ff685a60c66e84e69472b482f3271f3d0df41927b04da649ba9196abd1b68e6f042b3a82ff03e99406fb515450c05f7d0ab32c16a21199f9928892a7eae65137ce3edbd41b218cdb3bf209976b061c323f743c2e2e75cef1d17acde5a0425cd14a748fc6b2906b48ff685a60c66e84e69472b427b04da649ba9196b2e33ace0f1cb814308b3943c6b7c468364485aabb8af321364485aabb8af3212e2e75cef1d17acde5a0425cd14a748f886c70c8d9ca49c360c66e84e69472b4d55be5e290d9b221abd1b68e6f042b3a12c86f89b12b62475450c05f7d0ab32c60c66e84e69472b46f4ac06259840d3b5450c05f7d0ab32cb41a8950adc4000f12c86f89b12b6247dced51ab49cbee0ba7b2844e90a50368970b7ccb6db4a372256963e6d3e4b9d56e545d0a90e66b0fc5937b41f9568f66eaea1d27ed7f24f5f24ea9aebbe44dc15fbb9b7b4ec8634af2920db4e5adc7e5e682b954fc6a2bba0ec6170bffd88d0c17dd0ab3f1a36721d55be5e290d9b221468621e4436a9e31886c70c8d9ca49c3979fb166904c341c4a91989b5895a58004bc48faaf93c1dc16a21199f992889233e47bd64cf17df6610c77b9037c84e2886c70c8d9ca49c3c557eb0731a9f5d52e2e75cef1d17acd27c7b0bf0bab021c1dd40a9880fbcd5022e3230e7f009638408623e77c6b726ab62a1bec24edce0d836e7e981b18c4ffa7f7a433e9255ea5cb249176ac1b47de58fa9a38acbcebc7836e7e981b18c4ff2599d5844b4548f1839774cf8c545ff24a91989b5895a580836e7e981b18c4ff281ca13e4a9fbb7d1a70827770400c0735b33558bde8b2b5a7eae65137ce3edbcdbf9196ff295c00dfa47dafd2072b4b89ac760f62f6886989ac760f62f6886912c86f89b12b6247c938ce808bea6655839774cf8c545ff284a8a5657760904665429d5bdfecffbef0dfd8d3f0b0fd447eca954c5abef745da846df940582d3965350e2c031e292735b33558bde8b2b54aaeec80fed7543d6c9e5b466b56da46256963e6d3e4b9d51821404d558a611d300a240d2cc8fa72468621e4436a9e314a91989b5895a580b23ec550d6695990724075dde24450baf095ffeeeed6350ba4fc7e1d9bf7c53263caa56d61878019364485aabb8af32165429d5bdfecffbe16b71cf09c4f9f65256963e6d3e4b9d5256963e6d3e4b9d527c7b0bf0bab021c256963e6d3e4b9d51821404d558a611ddf31fa5d63b1044e256963e6d3e4b9d554acbded066f65b3256963e6d3e4b9d5256963e6d3e4b9d51821404d558a611dea187fd5f316c96c27c7b0bf0bab021c256963e6d3e4b9d5256963e6d3e4b9d5256963e6d3e4b9d51821404d558a611d16b71cf09c4f9f65d10e5110f6228c05f2c42fbd87cbe5299d2cd96b73bc76f15e4b975b3e4bedb0f095ffeeeed6350ba4fc7e1d9bf7c53263caa56d618780199b69c8a4a42a06939d2cd96b73bc76f19d2cd96b73bc76f163caa56d61878019281ca13e4a9fbb7d59283b4ec98580d163caa56d61878019281ca13e4a9fbb7d04bc48faaf93c1dc63caa56d61878019281ca13e4a9fbb7d33668886491f36551821404d558a611ddf31fa5d63b1044e256963e6d3e4b9d560c66e84e69472b4256963e6d3e4b9d5256963e6d3e4b9d5ea006f751ef6cdfe281ca13e4a9fbb7d89f6ba2d44b45ae71821404d558a611d16b71cf09c4f9f65a0607e2a5ad52b16145fee7cce42c3cb281ca13e4a9fbb7d9b5565c406ecdd2ef095ffeeeed6350ba4fc7e1d9bf7c53263caa56d6187801953c0ec97717a93bf33e47bd64cf17df660c66e84e69472b46dc75537007e4a5e89ac760f62f68869a7eae65137ce3edb2d0e17192233e5d04b22e562b2fa176d4cb25868e27a485da0bf29653220392463caa56d61878019b83d4bfb6ae764b0eaea1d27ed7f24f56dc75537007e4a5e89ac760f62f688697f8a6043d4b2b93ac5937b41f9568f66d10e5110f6228c05d10e5110f6228c05d10e5110f6228c0563caa56d618780194aaeec80fed7543d155652a810094f943be7bcd94c23f4f5256963e6d3e4b9d5256963e6d3e4b9d5d85345102587cef4eaea1d27ed7f24f5bac9b571058b788eb6ffbdc24fb38e9218d642ac9616356ff095ffeeeed6350bf095ffeeeed6350bf583aa02d899c238c938ce808bea66552e2e75cef1d17acd364485aabb8af321e5a0425cd14a748f364485aabb8af3212e2e75cef1d17acd976b061c323f743c357001074f4d24a12e2e75cef1d17acd99cf9b5369eda715f583aa02d899c238256963e6d3e4b9d5308b3943c6b7c468b5696f8b2efb25bc03a29b360a3e93341dd40a9880fbcd50"
	// data := []byte()
	lens := len(datass)
	// 3DES加密密钥，长度必须为24字节
	key := []byte("0123456789abcdef01234567")
	// 创建3DES加密算法实例
	block, err := des.NewTripleDESCipher(key)
	if err != nil {
		panic(err)
	}
	// 创建CBC分组模式实例
	iv := []byte("12345678")
	mode := cipher.NewCBCEncrypter(block, iv)
	for i := 0; i < lens; i += 16 {
		end := i + 16
		fmt.Println("", i, end)
		if end > lens {
			end = lens
		}
		// 创建CBC分组模式实例
		mode = cipher.NewCBCDecrypter(block, iv)
		// ciphertext := datass[i:end]
		// 解密数据
		ciphertext := make([]byte, len(datass[i:end]))
		mode.CryptBlocks(ciphertext, datass[i:end])
		byteSlice := []byte(ciphertext)
		fmt.Println("", byteSlice)
		fmt.Printf("加密后的数据：%x\n", datass[i:end])

		plaintext := make([]byte, len(byteSlice))
		mode.CryptBlocks(plaintext, byteSlice)

		// 去除填充数据
		plaintext = pkcs5UnPadding(plaintext)

		fmt.Printf("解密后的数据：%x\n", plaintext)
		fmt.Println(datass[i:end])
		// hex := strconv.FormatInt(int64(data[i:end]), 16)
		// fmt.Println("十六进制:", hex)

		if i > 1 {
			break
		}
	}
	fmt.Printf("%x", datass)

}

// PKCS5去除填充算法
func pkcs5UnPadding(datas []byte) []byte {
	length := len(datas)
	fmt.Println("", length)
	unpadding := int(datas[length-1])
	return datas[:(length - unpadding)]
}