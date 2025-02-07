#include <stdio.h>
#include <stdlib.h>

extern void re_msg(char *msg);
extern int get_xattr(const char *file_path, const char *attr_name, char *value, ssize_t size);

int main() {
    char command[9000];
    char file_path[4096];
    char kv_cache_path[4096];

    while(1) {
        //读取消息队列
        re_msg(file_path);

        //读取扩展属性
        if(get_xattr(file_path, "user.kvcache", kv_cache_path, 4096) != 0) {
            printf("%s does not have kvcache\n", file_path);
            continue;
        }

        // 使用sprintf构建命令字符串
        sprintf(command, "python -m inf_llm.gen --model-path " \
        "Qwen/Qwen1.5-0.5B-Chat --inf-llm-config-path /home/aistudio/InfLLM/config/qwen-inf-llm.yaml " \
        "--prompt-file %s --store-kv-cache-file %s", file_path, kv_cache_path);

        //执行命令
        system(command);
    }

    return 0;
}