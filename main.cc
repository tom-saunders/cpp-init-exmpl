#include "main.h"

#include "base.h"

#include <atomic>
#include <cstdio>

std::atomic<uint32_t> o_cnt;
// this is a _terrible_ idea
#define O(body) \
    printf("\n+O%u\t" # body "\n", ++o_cnt); \
    body; \
    printf("-o%u\n", o_cnt--)

#define P(v) \
    printf("+P\n");\
    printf("" # v ":\t[%s]\n-p\n", (v).ident().c_str())


void deferred_init() {
    O(Base b_defl{});
    P(b_defl);

    O(Holder h_def{Deferred{}});
    P(h_def);

    O(h_def.init(b_defl));
    P(h_def);
    P(b_defl);

    printf("return;\n");
    return;
}

void deferred_copy_init() {
    O(Base const b_defl{});
    P(b_defl);

    O(Holder h_def{Deferred{}});
    P(h_def);

    O(h_def.copy_init(b_defl));
    P(h_def);
    P(b_defl);

    printf("return;\n");
    return;
}

void deferred_move_init() {
    O(Base b_defl{});
    P(b_defl);

    O(Holder h_def{Deferred{}});
    P(h_def);

    O(h_def.move_init(std::move(b_defl)));
    P(h_def);
    P(b_defl);

    printf("return;\n");
    return;
}

int main()
{
    O(deferred_init());

    O(deferred_copy_init());

    O(deferred_move_init());

    printf("return 0;\n");
    return 0;
}

int x_x_main() {

    O(Base const b_default{});
    P(b_default);

    O(Base b_copy{b_default});
    P(b_copy);

    O(Holder h_def{Deferred{}});
    P(h_def);

    O(h_def.init(b_default));
    P(h_def);

    O(h_def.copy_init(b_default));
    P(h_def);

    O(h_def.move_init(std::move(b_copy)));
    P(h_def);

    printf("return 0;\n");
    return 0;
}
