#include<iostream>

struct TILE{
    int x; // sumbu j
    int y; // sumbu i
    bool isPassable;
};

struct PLAYER{
    int x; //sumbu j
    int y; //sumbu i
    int stamina;
};

char mapSource[10][10] = { //' ' -> jalan, 'w' -> wall , 's' -> start, 'f' -> finish
        {'w','w','w',' ',' ','w',' ',' ',' ',' '},
        {'w','f','w',' ',' ','w',' ','w','w',' '},
        {'w','w','w',' ',' ','w',' ','w',' ',' '},
        {' ','w',' ',' ','w','w',' ','w',' ','w'},
        {' ','w',' ',' ',' ',' ',' ','w',' ',' '},
        {' ','w',' ',' ',' ',' ',' ','w',' ','w'},
        {' ','w','w',' ',' ',' ',' ','w',' ',' '},
        {' ',' ',' ','w','w','w',' ','w','w',' '},
        {' ',' ',' ','w','s','w','w','w','w',' '},
        {' ',' ',' ','w',' ',' ',' ',' ',' ',' '}
};

void showStats(PLAYER player);

int main(){
    TILE map[10][10];
    TILE startTile = {
            .x = 4,
            .y = 8,
            .isPassable = true
    };
    TILE endTile = {
            .x = 1,
            .y = 1,
            .isPassable = true
    };
    PLAYER player = {
            .x = startTile.x,
            .y = startTile.y,
            .stamina = 10
    };
    //generate map
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            bool isPassable;
            if(mapSource[i][j]=='w'){
                isPassable = false;
            }
            else{
                isPassable = true;
            }
            TILE tile = {
                    .x = j,
                    .y = i,
                    .isPassable = isPassable
            };
            map[i][j] = tile;
        }
    }
    //main
    char input;
    std::cout<<"Welcome to Impossible game in which you cannot solve this game using normal means\n";
    std::cout<<"Use out-of-the box method to solve it!\n";
    std::cout<<"You only have some stamina to solve it. IF you run out of stamina before reaching end line, You LOSE!\n";
    std::cout<<"Each move cost 1 stamina.\n";
    std::cout<<"Start now? (y/n) \n";
    std::cin>>input;
    //cek input
    if(input=='y'){
        //get input
        while((player.x!=endTile.x || player.y!=endTile.y) && player.stamina){
            showStats(player);
            std::string dir;
            std::cout<<"Select where you want to move (UP,RIGHT,DOWN,LEFT): ";
            std::cin>>dir;
            if(dir=="UP" ){
                if(player.y ==0){
                    std::cout<<"You hit invisible wall!\n"<<std::endl;
                }
                else if(map[player.y-1][player.x].isPassable){
                    player.y --;
                    player.stamina--;
                }
                else{
                    std::cout<<"You hit a wall!\n"<<std::endl;
                }
            }
            else if(dir=="RIGHT" ){
                if(player.x ==9){
                    std::cout<<"You hit invisible wall!\n"<<std::endl;
                }
                else if(map[player.y][player.x+1].isPassable){
                    player.x ++;
                    player.stamina--;
                }
                else{
                    std::cout<<"You hit a wall!\n"<<std::endl;
                }
            }
            else if(dir=="DOWN"){
                if(player.y==9) {
                    std::cout << "You hit invisible wall!\n" << std::endl;
                }
                else if(map[player.y+1][player.x].isPassable){
                    player.y ++;
                    player.stamina--;
                }
                else{
                    std::cout<<"You hit a wall!\n"<<std::endl;
                }
            }
            else if(dir=="LEFT"){
                if(player.x==0){
                    std::cout << "You hit invisible wall!\n" << std::endl;
                }
                if(map[player.y][player.x-1].isPassable){
                    player.x --;
                    player.stamina--;
                }
                else{
                    std::cout<<"You hit a wall!\n"<<std::endl;
                }
            }
            else{
                std::cout<<"Invalid MOV!"<<std::endl;
            }
        }
        //cek
        if(player.x==endTile.x && player.y==endTile.y){
            std::cout<<"IMPOSSIBLE!!? How can you beat this impossible game!?"<<std::endl;
            std::cout<<"Nevermind, here's your prize:"<<std::endl;
            // cause segmentation fault on purpose
            int* nullPointer = nullptr;
            *nullPointer = 0;
        }
        else{
            std::cout<<"YOU LOSE!! BETTER TRY NEXT TIME (Though it is impossible)"<<std::endl;
        }
    }
    else{
        std::cout<<"Bye-bye loser!\n";
    }

    return 0;
}

void showStats(PLAYER player){
    std::cout<<"Coordinate: ("<<player.x<<","<<player.y<<")"<<std::endl;
    std::cout<<"Stamina: "<<player.stamina<<std::endl;
}