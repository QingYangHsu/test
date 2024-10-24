#include <iostream>
#include <string>
#include <curl/curl.h>

// 回调函数，用于处理从服务器返回的数据（在这个例子中我们不处理，直接忽略）
size_t callback(void *contents, size_t size, size_t nmemb, void *userp) {
    // 计算实际的字节数
    size_t real_size = size * nmemb;

    // 转换指针类型
    char* data = static_cast<char*>(contents);

    // 将返回的数据写入标准输出
    std::cout.write(data, real_size);
    
    // 必须返回实际的字节数
    return real_size;
}

int main() {
    CURL *curl;
    CURLcode res;

    // 初始化 libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // 创建一个 curl 对象
    curl = curl_easy_init();
    
    if(curl) {
        std::string webhook_url = "https://open.feishu.cn/open-apis/bot/v2/hook/your-webhook-url";
        std::string json_data = R"({
            "msg_type": "text",
            "content": {
                "text": "这是一条测试消息"
            }
        })";

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // 设置目标 URL
        curl_easy_setopt(curl, CURLOPT_URL, webhook_url.c_str());
        // 设置请求头
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // 设置 POST 数据
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
        // 设置回调函数处理服务器返回的数据
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        
        // 执行请求
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        std::cout<<"ok"<<std::endl;
        // 清理
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    // 清理 libcurl 全局资源
    curl_global_cleanup();

    return 0;
}
