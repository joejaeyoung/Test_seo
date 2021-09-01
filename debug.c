#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define false 0
#define true 1

typedef struct member{
    char id[20];
    char pwd[20];
    char name[20];
    struct member *next;
}member;

member *HEAD;

// 메뉴 함수
void openFiles(void);
void showMenu(void);        // 초기 메뉴 출력
int getMenuNum(void);       // 초기 메뉴에서 어떤 기능 실행할지 받고 리턴
void driveMenu(int);        // 각 메뉴 실행
void showSignUpMenu(void);  // 회원가입 메뉴 출력

// 각 메뉴 실행 함수
void signUp(void);          // 회원가입
void logIn(void);           // 로그인
void logOut(void);          // 로그아웃
void matchWord(void);       // 영어 단어 맞추기
void Withdrawal(void);      // 회원탈퇴
void terminate(void);       // 프로그램 종료

// 회원 관리 함수
member* get_member_info(void);  // 회원 정보 링크드 리스트에 저장
_Bool isExist(char*);            // 아이디 중복 확인

// 디버깅 함수
void printLinkedList(void);     // 현재 리스트 출력

int currID;                 // 현재 로그인 된 id
_Bool isLogined = false;    // 로그인 여부 (true : 로그인 상태 / false : 로그아웃 상태)
FILE *word;                 // 영단어 파일
FILE *member_info;          // 멤버 정보 파일

int main(int argc, char const *argv[]){
    
    openFiles();

    showMenu();

    return 0;
}

void openFiles(void){
   if ((member_info = fopen("member_info.txt", "r+")) == NULL) {
      printf("파일열기 실패\n");
        exit(true);
   }
    if ((word = fopen("dic.txt", "r+")) == NULL) {
      printf("파일열기 실패\n");
        exit(true);
   }
}

void showMenu(void){
    while(1){
        if ((member_info = fopen("member_info.txt", "r+")) == NULL) {
            printf("파일열기 실패\n");
            exit(true);
        }
        HEAD = malloc(sizeof(member));
        HEAD -> next = get_member_info();
        printLinkedList();

        // system("clear()");
        printf("==================================\n");    // 34
        printf("=========== 2021 SPLUG ===========\n");
        if(isLogined==false){
            printf("==================================\n");     // 로그아웃 상태
        }
        else{
            printf("======================= %s\n",&currID);     // 로그인 상태
        }
        printf("==================================\n");
        printf("=              메뉴              =\n");
        printf("==================================\n");
        printf("           1 .회원가입             \n");
        printf("           2. 로그인               \n");
        printf("           3. 로그아웃             \n");
        printf("           4. 영어 단어 맞추기     \n");
        printf("           5. 회원탈퇴             \n");
        printf("           6. 프로그램 종료        \n");
        printf("==================================\n");
        printf(": ");
        driveMenu(getMenuNum());
    }

}

void driveMenu(int menuNum){
    switch(menuNum){
        case 1:
            signUp();           // 회원가입 실행
            break;
        case 2:
            logIn();            // 로그인 실행
            break;
        case 3:
            logOut();           // 로그아웃 실행
            break;
        case 4:
            matchWord();        // 영어 단어 맞추기 실행
            break;
        case 5:
            Withdrawal();       // 회원탈퇴 실행
            break;
        case 6:
            terminate();        // 프로그램 종료 실행
            break;
        default :
            printf("잘못된 입력입니다. \n");    // 1~6 이외의 입력을 받았을 경우

    }
}

int getMenuNum(void) {
    int menuNum;
    scanf("%d",&menuNum);

    return menuNum;
}

void signUp(void){
    get_member_info();      // 회원 정보 불러오기
    showSignUpMenu();       // 회원가입
    return;
}       
void logIn(void){
    return;
}                  
void logOut(void){
    return;
}               
void matchWord(void){
    return;
}             
void Withdrawal(void){
    return;
}           

void terminate(void){
    printf("다음에 또 만나요!!\n");
    fclose(word);
    fclose(member_info);
    exit(true);
}

member* get_member_info(void){
    member temp_node={0,};
    
    int check = fscanf(member_info, "%s %s %s", temp_node.id, temp_node.pwd, temp_node.name);
    member *new_node;

    if(check == EOF) return NULL;   // 더 이상 가져올 정보 없을 경우

    new_node = malloc(sizeof(member));
    memset(new_node, 0 ,sizeof(member));
    strcpy(new_node -> id, temp_node.id);
    strcpy(new_node -> pwd, temp_node.pwd);
    strcpy(new_node -> name, temp_node.name);
    new_node -> next = get_member_info();
    return new_node;
}

void showSignUpMenu(void){
    char temp_id[20], temp_pwd[20], temp_name[20];
    memset(temp_id,0,sizeof(char)*20);
    memset(temp_pwd,0,sizeof(char)*20);
    memset(temp_name,0,sizeof(char)*20);
    printf("회원가입 페이지\n");
    
    printf("아이디 : ");
    scanf("%s", temp_id);
    while(1){
        if(isExist(temp_id)==false) break; // 아이디 중복이 아닐 경우
        printf("이미 존재하는 아이디 입니다\n");
        printf("아이디 : ");
        scanf("%s", temp_id);
    }
    printf("사용가능한 아이디 입니다.\n");
    printf("비밀번호 : ");
    scanf("%s", temp_pwd);
    printf("이름 : ");
    scanf("%s", temp_name);
    fprintf(member_info,"\n%s %s %s", temp_id, temp_pwd, temp_name);
    fclose(member_info);
}

_Bool isExist(char* id){
    member *curr_node = malloc(sizeof(member));
    curr_node = HEAD ;
    while(curr_node -> next!=NULL){
        printf("%s ", curr_node -> id);

        if(!strcmp(id, curr_node -> id)){
            return true;
        }
        curr_node = curr_node->next;
    }
    if(!strcmp(id, curr_node -> id)){
         return true;
    }

    return false;
}

void printLinkedList(void){
    member *curr_node = malloc(sizeof(member));
    curr_node = HEAD -> next;
    while(curr_node != NULL){
        printf("id : %s pwd : %s\n", curr_node -> id, curr_node -> pwd);
        curr_node = curr_node -> next;
    }
    
    return;
}