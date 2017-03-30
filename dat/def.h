/*プリプロセッサの一部である*/

//席ぎめをさせる奴らの最大数
#define STUDENT_MAX 49

//if(MODE='w')初期化
//else 席ぎめ実行
#define MODE 'r'

//if(OUT_MODE=0)1～最大数　表示
//if(OUT_MODE=1)　(i / GROUP_MAX +1)の(i / GROUP_MAX +1)　表示　→　グループ分け表示
#define OUT_MODE 1

//OUT_MODEが1の時→グループ分け表示のためのグループ最大数。
//最大数の約数だと嬉しいな♪
#define GROUP_MAX 7

#define WINDOW_SIZE true