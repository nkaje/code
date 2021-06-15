#include <stdio.h>
#include <stdint.h>

#define FEATURE_MAX 8

#define FEATURE_A   0x00000001
#define FEATURE_B   0x00000002
#define FEATURE_C   0x00000004
#define FEATURE_D   0x00000008

uint32_t feature = FEATURE_A;

void enable_features(uint32_t inp)
{
    int i;
    uint32_t en = (inp ^ feature) & ~feature;
	printf("current features 0x%x, features to enable 0x%x\n", feature, en);
	for (i = 0; i < FEATURE_MAX; i++) {
		if (en & (1 << i)) {
			printf("enabling 0x%x\n", (1 << i));
			feature |= (1 << i);
		}
	}
}

void disable_features(uint32_t inp)
{
    int i;
    uint32_t dis;

    dis = (inp & feature);
	printf("current features 0x%x, features to disable 0x%x\n", feature, dis);    
	for (i = 0; i < FEATURE_MAX; i++) {
		if (dis & (1 << i)) {
			printf("disabling 0x%x\n", (1 << i));
			feature &= ~(1 << i);
		}
 	}
}

int main(void)
{
    int test_count = 0;
    printf("current features 0x%x\n", feature);

    test_count++;
    enable_features(FEATURE_A|FEATURE_B|FEATURE_C);
    if (feature != (FEATURE_A|FEATURE_B|FEATURE_C)) {
        printf("test case %d failed\n", test_count);
        return 0;
    }

    test_count++;
    printf("current features 0x%x\n", feature);
    disable_features(FEATURE_A);
    if (feature != (FEATURE_B|FEATURE_C)) {
       printf("test case %d failed\n", test_count);
       return 0;
    }

    test_count++;
    printf("--current features 0x%x\n", feature);
    enable_features(FEATURE_B);
    if (feature != (FEATURE_B|FEATURE_C)) {
		printf("test case %d failed\n", test_count);
		return 0;
	}

    test_count++;
    disable_features(FEATURE_D);
    if (feature != (FEATURE_B|FEATURE_C)) {
       printf("test case %d failed\n", test_count);
       return 0;
    }
    printf("test successful, count %d\n", test_count);
    return 0;
}
