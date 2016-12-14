#include "queue.h"

void list(void);
void array(void);

float t1 = 0, t2 = 6, t3 = 0, t4 = 1;
float time_model;                     // ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ¬ֳ®ֳ₪ֳ¥ֳ«ֳ¨ֳ°ֳ®ֳ¢ֳ ֳ­ֳ¨ֳ¿
float idle_time;                      // ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ¯ֳ°ֳ®ֳ±ֳ²ֳ®ֳ¿
float twait;                          // ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ¯ֳ°ֳ¥ֳ¡ֳ»ֳ¢ֳ ֳ­ֳ¨ֳ¿ ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ× ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨
int N;                                // ֳ±ֳ·ֳ¥ֳ²ֳ·ֳ¨ֳ× ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ ֳ­ֳ­ֳ»ֳµ ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×
int Nwork;                            // ֳ×ֳ®ֳ«ֳ¨ֳ·ֳ¥ֳ±ֳ²ֳ¢ֳ® ֳ±ֳ°ֳ ֳ¡ֳ ֳ²ֳ»ֳ¢ֳ ֳ­ֳ¨ֳ© ֳ\00ֳ€
int count_in;                         // ֳ×ֳ®ֳ«ֳ¨ֳ·ֳ¥ֳ±ֳ²ֳ¢ֳ® ֳ¢ֳ®ֳ¸ֳ¥ֳ₪ֳ¸ֳ¨ֳµ ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×

void print_info(void)
{
    printf("\nֳ\00ֳ¡ֳ¹ֳ¥ֳ¥ ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ¬ֳ®ֳ₪ֳ¥ֳ«ֳ¨ֳ°ֳ®ֳ¢ֳ ֳ­ֳ¨ֳ¿: %0.2f\n", time_model);
    printf("ֳ\00ֳ®ֳ«"
           "ֳ¨ֳ·ֳ¥ֳ±ֳ²ֳ¢ֳ® ֳ¢ֳ®ֳ¸ֳ¥ֳ₪ֳ¸ֳ¨ֳµ ֳ¢ ֳ±ֳ¨ֳ±ֳ²ֳ¥ֳ¬ֳ³ ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×: %d\n", count_in);
    printf("ֳ\00ֳ®ֳ«ֳ¨ֳ·ֳ¥ֳ±ֳ²ֳ¢ֳ® ֳ¢ֳ»ֳ¸ֳ¥ֳ₪ֳ¸ֳ¨ֳµ ֳ¨ֳ§ ֳ±ֳ¨ֳ±ֳ²ֳ¥ֳ¬ֳ» ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×: %d\n", N);
    if (N != 0)
        printf("ֳ‘ֳ°ֳ¥ֳ₪ֳ­ֳ¥ֳ¥ ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ¯ֳ°ֳ¥ֳ¡ֳ»ֳ¢ֳ ֳ­ֳ¨ֳ¿ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨: %0.2f\n", twait/N);
    printf("ֳ‚ֳ°ֳ¥ֳ¬ֳ¿ ֳ¯ֳ°ֳ®ֳ±ֳ²ֳ®ֳ¿ ֳ\00ֳ€: %0.2f\n", idle_time);
    printf("ֳ\00ֳ®ֳ«ֳ¨ֳ·ֳ¥ֳ±ֳ²ֳ¢ֳ® ֳ±ֳ°ֳ ֳ¡ֳ ֳ²ֳ»ֳ¢ֳ ֳ­ֳ¨ֳ© ֳ\00ֳ€: %d\n", Nwork);
    printf("\nֳ\00ֳ®ֳ£ֳ°ֳ¥ֳ¸ֳ­ֳ®ֳ±ֳ²ֳ¼ ֳ¯ֳ® ֳ¢ֳµֳ®ֳ₪ֳ³: %f\n", \
           (fabs(count_in - 2*time_model/(t2+t1))/(2*time_model/(t2+t1))) * 100);
    printf("ֳ\00ֳ®ֳ£ֳ°ֳ¥ֳ¸ֳ­ֳ®ֳ±ֳ²ֳ¼ ֳ¯ֳ® ֳ¢ֳ»ֳµֳ®ֳ₪ֳ³: %f\n", \
           (fabs(Nwork*(t4+t3)/2 + idle_time - time_model)/(Nwork*(t4+t3)/2 + idle_time)) * 100);
}

// ֳ’ֳ¥ֳ±ֳ²ֳ¨ֳ°ֳ®ֳ¢ֳ ֳ­ֳ¨ֳ¥ ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ³ֳ₪ֳ ֳ«ֳ¥ֳ­ֳ¨ֳ¿ ֳ¨ ֳ₪ֳ®ֳ¡ֳ ֳ¢ֳ«ֳ¥ֳ­ֳ¨ֳ¿ ֳ½ֳ«ֳ¥ֳ¬ֳ¥ֳ­ֳ²ֳ®ֳ¢.
void time_test(void)
{
    struct queue_list *q_list;
    struct request_list *a_list;
    struct queue_array *q_array;
    struct request_array a_array;

    double begin_en = 0, end_en = 0;
    double begin_de = 0, end_de = 0;

    q_list = malloc(sizeof(struct queue_list));
    init_list(q_list);
    q_array = malloc(sizeof(struct queue_array));
    init_array(q_array);

    for (int j = 0; j < 1000; j++)
    {
        for (int i = 0; i < MAX_ARRAY; i++)
        {
            begin_en += clock()/(float)CLOCKS_PER_SEC;
            a_array = create_request_array(t1, t2, t3, t4);
            enqueue_array(q_array, a_array);
            end_en += clock()/(float)CLOCKS_PER_SEC;
        }
        for (int i = 0; i < MAX_ARRAY; i++)
        {
            begin_de += clock()/(float)CLOCKS_PER_SEC;
            dequeue_array(q_array);
            end_de += clock()/(float)CLOCKS_PER_SEC;
        }
    }
    free(q_array);
    printf("\nֳ\00ֳ ֳ±ֳ±ֳ¨ֳ¢.\n");
    printf("ֳ‚ֳ°ֳ¥ֳ¬ֳ¿ ֳ₪ֳ®ֳ¡ֳ ֳ¢ֳ«ֳ¥ֳ­ֳ¨ֳ¿ %d ֳ½ֳ«ֳ¥ֳ¬ֳ¥ֳ­ֳ²ֳ®ֳ¢ (ֳ¬ֳ±): %lf\n", MAX_ARRAY, (end_en - begin_en));
    printf("ֳ‚ֳ°ֳ¥ֳ¬ֳ¿ ֳ³ֳ₪ֳ ֳ«ֳ¥ֳ­ֳ¨ֳ¿ %d ֳ½ֳ«ֳ¥ֳ¬ֳ¥ֳ­ֳ²ֳ®ֳ¢ (ֳ¬ֳ±): %lf\n", MAX_ARRAY, (end_de - begin_de));
    printf("ֳ‡ֳ ֳ­ֳ¨ֳ¬ֳ ֳ¥ֳ¬ֳ ֳ¿ ֳ¯ֳ ֳ¬ֳ¿ֳ²ֳ¼: %ld\n\n", sizeof(struct queue_array));

    begin_en = 0;
    end_en = 0;
    begin_de = 0;
    end_de = 0;
    for (int j = 0; j < 1000; j++)
    {
        for (int i = 0; i < MAX_ARRAY; i++)
        {
            begin_en += clock()/(float)CLOCKS_PER_SEC;
            a_list = (struct request_list*)malloc(sizeof(struct request_list));
            create_request_list(a_list, t1, t2, t3, t4);
            enqueue_list(q_list, a_list);
            end_en += clock()/(float)CLOCKS_PER_SEC;
        }
        for (int i = 0; i < MAX_ARRAY; i++)
        {
            begin_de += clock()/(float)CLOCKS_PER_SEC;
            dequeue_list(q_list);
            end_de += clock()/(float)CLOCKS_PER_SEC;
        }
    }
    free(q_list);
    printf("ֳ‘ֳ¢ֳ¿ֳ§ֳ­ֳ»ֳ© ֳ±ֳ¯ֳ¨ֳ±ֳ®ֳ×.\n");
    printf("ֳ‚ֳ°ֳ¥ֳ¬ֳ¿ ֳ₪ֳ®ֳ¡ֳ ֳ¢ֳ«ֳ¥ֳ­ֳ¨ֳ¿ %d ֳ½ֳ«ֳ¥ֳ¬ֳ¥ֳ­ֳ²ֳ®ֳ¢ (ֳ¬ֳ±): %lf\n", MAX_ARRAY, (end_en - begin_en));
    printf("ֳ‚ֳ°ֳ¥ֳ¬ֳ¿ ֳ³ֳ₪ֳ ֳ«ֳ¥ֳ­ֳ¨ֳ¿ %d ֳ½ֳ«ֳ¥ֳ¬ֳ¥ֳ­ֳ²ֳ®ֳ¢ (ֳ¬ֳ±): %lf\n", MAX_ARRAY, (end_de - begin_de));
    printf("ֳ‡ֳ ֳ­ֳ¨ֳ¬ֳ ֳ¥ֳ¬ֳ ֳ¿ ֳ¯ֳ ֳ¬ֳ¿ֳ²ֳ¼: %ld\n", sizeof(struct queue_list)*MAX_ARRAY+sizeof(struct request_list));

    return;
}

// ֳ\00ֳ°ֳ®ֳ¢ֳ¥ֳ°ֳ×ֳ  ֳ´ֳ°ֳ ֳ£ֳ¬ֳ¥ֳ­ֳ²ֳ ֳ¶ֳ¨ֳ¨ ֳ¯ֳ ֳ¬ֳ¿ֳ²ֳ¨
void check_fragmentation(void)
{
    struct queue_list *q_list;
    struct request_list *a_list;
    int chf = 0;
    q_list = malloc(sizeof(struct queue_list));
    init_list(q_list);
    chf = -1;
    while (chf != 0)
    {
        system("cls");
        print_list(q_list);

        // ֳ\00ֳ¥ֳ­ֳ¾.
        printf("0. ֳ\00ֳ ֳ§ֳ ֳ₪.\n1. ֳ„ֳ®ֳ¡ֳ ֳ¢ֳ¨ֳ²ֳ¼ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ³ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼.\n2. ֳ“ֳ₪ֳ ֳ«ֳ¨ֳ²ֳ¼ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ³ ֳ¨ֳ§ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨.\n");
        printf("\nֳ\00ֳ®ֳ¬ֳ ֳ­ֳ₪ֳ : ");

        if (scanf("%d", &chf) == 0) break;
        switch (chf)
        {
        case 0:
            break;
        case 1:
            a_list = (struct request_list*)malloc(sizeof(struct request_list));
            create_request_list(a_list, t1, t2, t3, t4);
            enqueue_list(q_list, a_list);
            break;
        case 2:
            if (isempty_list(q_list) != 1)
                dequeue_list(q_list);
            else
            {
                fflush(stdin);
                printf("ֳ\00ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼ ֳ¯ֳ³ֳ±ֳ²ֳ !\n");
                getchar();
            }
            break;
        default:
            printf("ֳ\00ֳ¸ֳ¨ֳ¡ֳ×ֳ  ֳ¢ֳ¢ֳ®ֳ₪ֳ  ֳ×ֳ®ֳ¬ֳ ֳ­ֳ₪ֳ».\n");
            fflush(stdin); getchar();
            break;
        }
    }
    while (isempty_list(q_list) != 1)
        dequeue_list(q_list);
    free(q_list);
    return;
}

int main()
{
    system("chcp 1251");
    int choose = 0;      // ֳ×ֳ®ֳ¬ֳ ֳ­ֳ₪ֳ  ֳ¬ֳ¥ֳ­ֳ¾
    while (choose != 7)
    {
        time_model = 0;
        idle_time = 0;
        twait = 0;
        N = 0;
        Nwork = 0;
        count_in = 0;

        system("cls");

        // ֳ\00ֳ¥ֳ­ֳ¾.
        printf("ֳ\00ֳ°ֳ®ֳ£ֳ°ֳ ֳ¬ֳ¬ֳ  ֳ¬ֳ®ֳ₪ֳ¥ֳ«ֳ¨ֳ°ֳ³ֳ¥ֳ² ֳ¯ֳ°ֳ®ֳ¶ֳ¥ֳ±ֳ± ֳ®ֳ¡ֳ±ֳ«ֳ³ֳ¦ֳ¨ֳ¢ֳ ֳ­ֳ¨ֳ¿ ֳ₪ֳ® ֳ³ֳµֳ®ֳ₪ֳ  ֳ¨ֳ§ ֳ±ֳ¨ֳ±ֳ²ֳ¥ֳ¬ֳ» 1000 ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×.\n\n");
        printf("ֳˆֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ« ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ¯ֳ°ֳ¨ֳµֳ®ֳ₪ֳ  ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨: [%0.2f, %0.2f]\n", t1, t2);
        printf("ֳˆֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ« ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ¨ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨: [%0.2f, %0.2f]\n\n", t3, t4);
        printf("1. ֳ\00ֳ ֳ±ֳ±ֳ¨ֳ¢.\n2. ֳ‘ֳ¢ֳ¿ֳ§ֳ­ֳ»ֳ© ֳ±ֳ¯ֳ¨ֳ±ֳ®ֳ×.\n3. ֳˆֳ§ֳ¬ֳ¥ֳ­ֳ¨ֳ²ֳ¼ ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ« ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ¯ֳ°ֳ¨ֳµֳ®ֳ₪ֳ  ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨.\n"
                "4. ֳˆֳ§ֳ¬ֳ¥ֳ­ֳ¨ֳ²ֳ¼ ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ« ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ¨ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨.\n5. ֳ\00ֳ°ֳ®ֳ¢ֳ¥ֳ°ֳ¨ֳ²ֳ¼ ֳ´ֳ°ֳ ֳ£ֳ¬ֳ¥ֳ­ֳ²ֳ ֳ¶ֳ¨ֳ¾ ֳ¯ֳ ֳ¬ֳ¿ֳ²ֳ¨."
                "\n6. ֳ‘ֳ°ֳ ֳ¢ֳ­ֳ¨ֳ²ֳ¼ ֳ°ֳ ֳ§ֳ«ֳ¨ֳ·ֳ­ֳ»ֳ¥ ֳ°ֳ¥ֳ ֳ«ֳ¨ֳ§ֳ ֳ¶ֳ¨ֳ¨ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨ ֳ¯ֳ® ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ¨ ֳ¯ֳ ֳ¬ֳ¿ֳ²ֳ¨.\n7. ֳ‚ֳ»ֳµֳ®ֳ₪.\n\nֳ\00ֳ®ֳ¬ֳ ֳ­ֳ₪ֳ : ");

        if (scanf("%d", &choose) == 0) break;

        switch (choose)
        {
        case 1:
            array();            // ֳ°ֳ¥ֳ ֳ«ֳ¨ֳ§ֳ ֳ¶ֳ¨ֳ¿ ֳ¬ֳ ֳ±ֳ±ֳ¨ֳ¢ֳ®ֳ¬
            print_info();
            fflush(stdin);
            getchar();
            break;
        case 2:
            list();             // ֳ°ֳ¥ֳ ֳ«ֳ¨ֳ§ֳ ֳ¶ֳ¨ֳ¿ ֳ±ֳ¯ֳ¨ֳ±ֳ×ֳ®ֳ¬
            print_info();
            fflush(stdin);
            getchar();
            break;
        case 3:
            printf("ֳ‚ֳ¢ֳ¥ֳ₪ֳ¨ֳ²ֳ¥ ֳ­ֳ ֳ·ֳ ֳ«ֳ® ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ«ֳ  ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ¯ֳ°ֳ¨ֳµֳ®ֳ₪ֳ : ");
            while (scanf("%f", &t1) == 0 || t1 < 0)
            {
                fflush(stdin);
                printf("ֳ\00ֳ¸ֳ¨ֳ¡ֳ×ֳ  ֳ¢ֳ¢ֳ®ֳ₪ֳ .\n");
                printf("ֳ‚ֳ¢ֳ¥ֳ₪ֳ¨ֳ²ֳ¥ ֳ­ֳ ֳ·ֳ ֳ«ֳ® ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ«ֳ  ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ¯ֳ°ֳ¨ֳµֳ®ֳ₪ֳ : ");
            }
            printf("ֳ‚ֳ¢ֳ¥ֳ₪ֳ¨ֳ²ֳ¥ ֳ×ֳ®ֳ­ֳ¥ֳ¶ ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ«ֳ  ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ¯ֳ°ֳ¨ֳµֳ®ֳ₪ֳ : ");
            while (scanf ("%f", &t2) == 0 || t2 <= 0 || t2 < t1)
            {
                fflush(stdin);
                printf("ֳ\00ֳ¸ֳ¨ֳ¡ֳ×ֳ  ֳ¢ֳ¢ֳ®ֳ₪ֳ .\n");
                printf("ֳ‚ֳ¢ֳ¥ֳ₪ֳ¨ֳ²ֳ¥ ֳ×ֳ®ֳ­ֳ¥ֳ¶ ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ«ֳ  ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ¯ֳ°ֳ¨ֳµֳ®ֳ₪ֳ  : ");
            }
            break;
        case 4:
            printf("ֳ‚ֳ¢ֳ¥ֳ₪ֳ¨ֳ²ֳ¥ ֳ­ֳ ֳ·ֳ ֳ«ֳ® ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ«ֳ  ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ¨: ");
            while (scanf("%f", &t3) == 0 || t3 < 0)
            {
                fflush(stdin);
                printf("ֳ\00ֳ¸ֳ¨ֳ¡ֳ×ֳ  ֳ¢ֳ¢ֳ®ֳ₪ֳ .\n");
                printf("ֳ‚ֳ¢ֳ¥ֳ₪ֳ¨ֳ²ֳ¥ ֳ­ֳ ֳ·ֳ ֳ«ֳ® ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ«ֳ  ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ¨: ");
            }
            printf("ֳ‚ֳ¢ֳ¥ֳ₪ֳ¨ֳ²ֳ¥ ֳ×ֳ®ֳ­ֳ¥ֳ¶ ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ«ֳ  ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ¨: ");
            while (scanf("%f", &t4) == 0 || t4 < 0 || t4 < t3)
            {
                fflush(stdin);
                printf("ֳ\00ֳ¸ֳ¨ֳ¡ֳ×ֳ  ֳ¢ֳ¢ֳ®ֳ₪ֳ .\n");
                printf("ֳ‚ֳ¢ֳ¥ֳ₪ֳ¨ֳ²ֳ¥ ֳ×ֳ®ֳ­ֳ¥ֳ¶ ֳ¨ֳ­ֳ²ֳ¥ֳ°ֳ¢ֳ ֳ«ֳ  ֳ¢ֳ°ֳ¥ֳ¬ֳ¥ֳ­ֳ¨ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ¨: ");
            }
            break;
        case 5:
            check_fragmentation();
            break;
        case 6:
            time_test();
            fflush(stdin); getchar();
            break;
        case 7:
            return 0;
            break;
        default:
            printf("ֳ\00ֳ¸ֳ¨ֳ¡ֳ×ֳ  ֳ¢ֳ¢ֳ®ֳ₪ֳ  ֳ×ֳ®ֳ¬ֳ ֳ­ֳ₪ֳ».\n");
            fflush(stdin); getchar();
            break;
        }
    }
    return 0;
}

void list(void)
{
    struct queue_list *q;
    struct request_list *a;
    struct request_list *r;

    float t = 0, ta = 0;     // ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ¨ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¨ ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ¯ֳ°ֳ¨ֳµֳ®ֳ₪ֳ  ֳ±ֳ«ֳ¥ֳ₪ֳ³ֳ¾ֳ¹ֳ¥ֳ©
    int P = 0;               // ֳ¢ֳ¥ֳ°ֳ®ֳ¿ֳ²ֳ­ֳ®ֳ±ֳ²ֳ¼
    float length = 0;        // ֳ®ֳ¡ֳ¹ֳ ֳ¿ ֳ₪ֳ«ֳ¨ֳ­ֳ  ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨
    int iter = 0;

    q = malloc(sizeof(struct queue_list));
    init_list(q);

    // ֳ„ֳ®ֳ¡ֳ ֳ¢ֳ«ֳ¿ֳ¥ֳ¬ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼ ֳ¯ֳ¥ֳ°ֳ¢ֳ³ֳ¾ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ³ ֳ¨ ֳ³ֳ₪ֳ ֳ«ֳ¿ֳ¥ֳ¬ ֳ¥ֵ¾.
    a = (struct request_list*)malloc(sizeof(struct request_list));
    create_request_list(a, t1, t2, t3, t4);
    enqueue_list(q, a);
    r = (struct request_list*)malloc(sizeof(struct request_list));
    *r = dequeue_list(q);
    t = r->time_of_processing;
    idle_time = r->time_of_arrival;

    // ֳ‘ֳ®ֳ§ֳ₪ֳ ֳ¥ֳ¬ ֳ­ֳ®ֳ¢ֳ³ֳ¾ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ³ - ֳ½ֳ²ֳ® ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ , ֳ×ֳ®ֳ²ֳ®ֳ°ֳ ֳ¿ ֳ₪ֳ®ֳ«ֳ¦ֳ­ֳ  ֳ±ֳ«ֳ¥ֳ₪ֳ³ֳ¾ֳ¹ֳ¥ֳ© ֳ¯ֳ°ֳ¨ֳ©ֳ²ֳ¨ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼
    a = (struct request_list*)malloc(sizeof(struct request_list));
    create_request_list(a, t1, t2, t3, t4);
    ta = a->time_of_arrival;

    while (N != 1000)
    {
        iter++;
        length+=q->len;

         /*
          * ֳ…ֳ±ֳ«ֳ¨ ֳ±ֳ«ֳ¥ֳ₪ֳ³ֳ¾ֳ¹ֳ ֳ¿ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ  ֳ¯ֳ°ֳ¨ֳ₪ֳ¥ֳ² ֳ¯ֳ®ֳ§ֳ¦ֳ¥, ֳ·ֳ¥ֳ¬ ֳ§ֳ ֳ×ֳ®ֳ­ֳ·ֳ¨ֳ²ֳ±ֳ¿ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ  ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¢ ֳ\00ֳ€, ֳ²ֳ®
          * ֳ§ֳ ֳ¢ֳ¥ֳ°ֳ¸ֳ ֳ¥ֳ¬ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ³ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¢ ֳ\00ֳ€ ֳ¨ ֳ­ֳ ֳ·ֳ¨ֳ­ֳ ֳ¥ֳ¬ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ ֳ²ֳ»ֳ¢ֳ ֳ²ֳ¼ ֳ±ֳ«ֳ¥ֳ₪ֳ³ֳ¾ֳ¹ֳ³ֳ¾ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨.
          * ֳˆֳ­ֳ ֳ·ֳ¥ - ֳ₪ֳ®ֳ¡ֳ ֳ¢ֳ«ֳ¿ֳ¥ֳ¬ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼ ֳ­ֳ®ֳ¢ֳ³ֳ¾ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ³.
         */

        if (t < ta)
        {
            time_wait_list(q, t);      // ֳ³ֳ¢ֳ¥ֳ«ֳ¨ֳ·ֳ¨ֳ¢ֳ ֳ¥ֳ¬ ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ®ֳ¦ֳ¨ֳ₪ֳ ֳ­ֳ¨ֳ¿ ֳ¢ֳ±ֳ¥ֳµ ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ× ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨
            if (isempty_list(q) == 0)
            {
                time_model += t;
                ta -= t;
            }
            else
            {
                time_model += ta;
                idle_time += ta - t;
                enqueue_list(q, a);
                count_in++;
                a = (struct request_list*)malloc(sizeof(struct request_list));
                create_request_list(a, t1, t2, t3, t4);
                ta = a->time_of_arrival;
            }

            r = (struct request_list*)malloc(sizeof(struct request_list));
            *r = dequeue_list(q);
            t = r->time_of_processing;
            Nwork++;

            // ֳ‚ֳ®ֳ§ֳ¢ֳ°ֳ ֳ¹ֳ¥ֳ­ֳ¨ֳ¥ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼, ֳ¥ֳ±ֳ«ֳ¨ ֳ±ֳ«ֳ³ֳ·ֳ ֳ©ֳ­ֳ®ֳ¥ ֳ·ֳ¨ֳ±ֳ«ֳ® P < 80.
            P = rand() % 100;
            if (P < 80)
            {
                r->downtime = 0;
                enqueue_list(q, r);
            }
            else
            {
                free(r);
                twait += r->downtime;
                N++;

                // ֳ\00ֳ¥ֳ·ֳ ֳ²ֳ¼ ֳ¯ֳ°ֳ®ֳ¬ֳ¥ֳ¦ֳ³ֳ²ֳ­ֳ®ֳ£ֳ® ֳ°ֳ¥ֳ§ֳ³ֳ«ֳ¼ֳ²ֳ ֳ²ֳ , ֳ¥ֳ±ֳ«ֳ¨ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ ֳ­ֳ® ֳ·ֳ¨ֳ±ֳ«ֳ® ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×, ֳ×ֳ°ֳ ֳ²ֳ­ֳ®ֳ¥ 100.
                if (N%100 == 0 && N != 0)
                {
                    printf("ֳ\00ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ ֳ­ֳ® ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×: %d\n", N);
                    printf("ֳ’ֳ¥ֳ×ֳ³ֳ¹ֳ ֳ¿ ֳ₪ֳ«ֳ¨ֳ­ֳ : %d, ", q->len);
                    printf("cֳ°ֳ¥ֳ₪ֳ­ֳ¿ֳ¿ ֳ₪ֳ«ֳ¨ֳ­ֳ : %0.2f\n\n", length/iter);
                }
            }
        }
        else
        {
            enqueue_list(q, a);
            count_in++;
            time_model += ta;
            a = (struct request_list*)malloc(sizeof(struct request_list));
            create_request_list(a, t1, t2, t3, t4);
            t -=  ta;
            ta = a->time_of_arrival;
        }
    }

    // ֳ\00ֳ±ֳ¢ֳ®ֳ¡ֳ®ֳ¦ֳ₪ֳ¥ֳ­ֳ¨ֳ¥ ֳ¯ֳ ֳ¬ֳ¿ֳ²ֳ¨
    while (isempty_list(q) != 1)
        *r = dequeue_list(q);
    free(q);
    return;
}


void array(void)
{
    struct queue_array *q;
    struct request_array a;
    struct request_array r;

    float t = 0, ta = 0;     // ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ¨ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¨ ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ¯ֳ°ֳ¨ֳµֳ®ֳ₪ֳ  ֳ±ֳ«ֳ¥ֳ₪ֳ³ֳ¾ֳ¹ֳ¥ֳ©
    int P = 0;               // ֳ¢ֳ¥ֳ°ֳ®ֳ¿ֳ²ֳ­ֳ®ֳ±ֳ²ֳ¼
    float length = 0;        // ֳ®ֳ¡ֳ¹ֳ ֳ¿ ֳ₪ֳ«ֳ¨ֳ­ֳ  ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨
    int iter = 0;

    q = malloc(sizeof(struct queue_array));
    init_array(q);

    // ֳ„ֳ®ֳ¡ֳ ֳ¢ֳ«ֳ¿ֳ¥ֳ¬ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼ ֳ¯ֳ¥ֳ°ֳ¢ֳ³ֳ¾ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ³ ֳ¨ ֳ³ֳ₪ֳ ֳ«ֳ¿ֳ¥ֳ¬ ֳ¥ֵ¾.
    a = create_request_array(t1, t2, t3, t4);
    enqueue_array(q, a);
    r = dequeue_array(q);
    t = r.time_of_processing;
    idle_time = r.time_of_arrival;

    // ֳ‘ֳ®ֳ§ֳ₪ֳ ֳ¥ֳ¬ ֳ­ֳ®ֳ¢ֳ³ֳ¾ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ³ - ֳ½ֳ²ֳ® ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ , ֳ×ֳ®ֳ²ֳ®ֳ°ֳ ֳ¿ ֳ₪ֳ®ֳ«ֳ¦ֳ­ֳ  ֳ±ֳ«ֳ¥ֳ₪ֳ³ֳ¾ֳ¹ֳ¥ֳ© ֳ¯ֳ°ֳ¨ֳ©ֳ²ֳ¨ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼
    a = create_request_array(t1, t2, t3, t4);
    ta = a.time_of_arrival;

    while (N != 1000)
    {
        length += (q->rear - q->frnt);
        iter++;

        /*
         * ֳ…ֳ±ֳ«ֳ¨ ֳ±ֳ«ֳ¥ֳ₪ֳ³ֳ¾ֳ¹ֳ ֳ¿ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ  ֳ¯ֳ°ֳ¨ֳ₪ֳ¥ֳ² ֳ¯ֳ®ֳ§ֳ¦ֳ¥, ֳ·ֳ¥ֳ¬ ֳ§ֳ ֳ×ֳ®ֳ­ֳ·ֳ¨ֳ²ֳ±ֳ¿ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ  ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¢ ֳ\00ֳ€, ֳ²ֳ®
         * ֳ§ֳ ֳ¢ֳ¥ֳ°ֳ¸ֳ ֳ¥ֳ¬ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ×ֳ³ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¢ ֳ\00ֳ€ ֳ¨ ֳ­ֳ ֳ·ֳ¨ֳ­ֳ ֳ¥ֳ¬ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ ֳ²ֳ»ֳ¢ֳ ֳ²ֳ¼ ֳ±ֳ«ֳ¥ֳ₪ֳ³ֳ¾ֳ¹ֳ³ֳ¾ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨.
         * ֳˆֳ­ֳ ֳ·ֳ¥ - ֳ₪ֳ®ֳ¡ֳ ֳ¢ֳ«ֳ¿ֳ¥ֳ¬ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼ ֳ­ֳ®ֳ¢ֳ³ֳ¾ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ³.
        */

        if (t < ta)
        {
            time_wait_array(q, t);           // ֳ³ֳ¢ֳ¥ֳ«ֳ¨ֳ·ֳ¨ֳ¢ֳ ֳ¥ֳ¬ ֳ¢ֳ°ֳ¥ֳ¬ֳ¿ ֳ®ֳ¦ֳ¨ֳ₪ֳ ֳ­ֳ¨ֳ¿ ֳ¢ֳ±ֳ¥ֳµ ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ× ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨
            if (isempty_array(q) == 0)
            {
                time_model += t;
                ta -= t;
            }
            else
            {
                idle_time += ta-t;
                time_model += ta;
                if (enqueue_array(q, a))
                {
                    printf("ֳ\00ֳ®ֳ₪ֳ¥ֳ«ֳ¨ֳ°ֳ®ֳ¢ֳ ֳ­ֳ¨ֳ¥ ֳ®ֳ±ֳ²ֳ ֳ­ֳ®ֳ¢ֳ«ֳ¥ֳ­ֳ®. ֳ\00ֳ°ֳ®ֳ¨ֳ§ֳ®ֳ¸ֳ«ֳ® ֳ¯ֳ¥ֳ°ֳ¥ֳ¯ֳ®ֳ«ֳ­ֳ¥ֳ­ֳ¨ֳ¥ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨.\n");
                    return;
                }
                count_in++;
                a = create_request_array(t1, t2, t3, t4);
                ta = a.time_of_arrival;
            }

            r = dequeue_array(q);
            t = r.time_of_processing;
            Nwork++;

            // ֳ‚ֳ®ֳ§ֳ¢ֳ°ֳ ֳ¹ֳ¥ֳ­ֳ¨ֳ¥ ֳ§ֳ ֳ¿ֳ¢ֳ×ֳ¨ ֳ¢ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¼, ֳ¥ֳ±ֳ«ֳ¨ ֳ±ֳ«ֳ³ֳ·ֳ ֳ©ֳ­ֳ®ֳ¥ ֳ·ֳ¨ֳ±ֳ«ֳ® P < 80.
            P = rand() % 100;
            if (P < 80)
            {
                r.downtime = 0;
                if (enqueue_array(q, r))
                {
                    printf("ֳ\00ֳ®ֳ₪ֳ¥ֳ«ֳ¨ֳ°ֳ®ֳ¢ֳ ֳ­ֳ¨ֳ¥ ֳ®ֳ±ֳ²ֳ ֳ­ֳ®ֳ¢ֳ«ֳ¥ֳ­ֳ®. ֳ\00ֳ°ֳ®ֳ¨ֳ§ֳ®ֳ¸ֳ«ֳ® ֳ¯ֳ¥ֳ°ֳ¥ֳ¯ֳ®ֳ«ֳ­ֳ¥ֳ­ֳ¨ֳ¥ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨.\n");
                    return;
                }
            }
            else
            {
                twait += r.downtime;
                N++;

                // ֳ\00ֳ¥ֳ·ֳ ֳ²ֳ¼ ֳ¯ֳ°ֳ®ֳ¬ֳ¥ֳ¦ֳ³ֳ²ֳ­ֳ®ֳ£ֳ® ֳ°ֳ¥ֳ§ֳ³ֳ«ֳ¼ֳ²ֳ ֳ²ֳ , ֳ¥ֳ±ֳ«ֳ¨ ֳ®ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ ֳ­ֳ® ֳ·ֳ¨ֳ±ֳ«ֳ® ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×, ֳ×ֳ°ֳ ֳ²ֳ­ֳ®ֳ¥ 100.
                if (N%100 == 0 && N != 0)
                {
                    printf("ֳ\00ֳ¡ֳ°ֳ ֳ¡ֳ®ֳ²ֳ ֳ­ֳ® ֳ§ֳ ֳ¿ֳ¢ֳ®ֳ×: %d\n", N);
                    printf("ֳ’ֳ¥ֳ×ֳ³ֳ¹ֳ ֳ¿ ֳ₪ֳ«ֳ¨ֳ­ֳ : %d, ", q->rear - q->frnt);
                    printf("cֳ°ֳ¥ֳ₪ֳ­ֳ¿ֳ¿ ֳ₪ֳ«ֳ¨ֳ­ֳ : %0.2f\n\n", length/iter);
                }
            }
        }
        else
        {
            if (enqueue_array(q, a))
            {
                printf("ֳ\00ֳ®ֳ₪ֳ¥ֳ«ֳ¨ֳ°ֳ®ֳ¢ֳ ֳ­ֳ¨ֳ¥ ֳ®ֳ±ֳ²ֳ ֳ­ֳ®ֳ¢ֳ«ֳ¥ֳ­ֳ®. ֳ\00ֳ°ֳ®ֳ¨ֳ§ֳ®ֳ¸ֳ«ֳ® ֳ¯ֳ¥ֳ°ֳ¥ֳ¯ֳ®ֳ«ֳ­ֳ¥ֳ­ֳ¨ֳ¥ ֳ®ֳ·ֳ¥ֳ°ֳ¥ֳ₪ֳ¨.\n");
                return;
            }
            count_in++;
            time_model += ta;
            a = create_request_array(t1, t2, t3, t4);
            t -=  ta;
            ta = a.time_of_arrival;
        }
    }

    // ֳ\00ֳ±ֳ¢ֳ®ֳ¡ֳ®ֳ¦ֳ₪ֳ¥ֳ­ֳ¨ֳ¥ ֳ¯ֳ ֳ¬ֳ¿ֳ²ֳ¨.
    free(q);
    return;
}