inline unsigned long hash(const std::string& str){
    unsigned long ret = 0;

    asm(R"(
        .intel_syntax noprefix
        lea rax, [%1]
        xor %0, %0

        xor rbx, rbx
    looop:
        mov bl ,byte ptr [rax]
        inc rax
        xor %0, rbx
        shl %0, 1
        cmp byte ptr [rax], 0
        jne looop

        .att_syntax prefix
    )"
    : "=r"(ret)
    : "r"(str.data())
    : "rax", "rcx", "rbx"
    );

    return ret;
}
