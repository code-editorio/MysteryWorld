#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <set>
#include <algorithm>
#include <string>
#include <tuple>
#include <limits>
using namespace std;


int randomnumber(int start, int end){
    int random = start + rand() % (end - start);
    return random;
}
pair<int,int> coordinate(){
    int x = randomnumber(1, 10);
    int y = randomnumber(1, 10);
    return make_pair(x, y);
}


class Entity{
    public:
    // Entity Types
    string entitycheck (char entitysymbol){
        switch (entitysymbol)
        {
        case 'S':
            return "Stone";
            break;
        case 'O':
            return "Hole";
            break;
        case '@':
            return "Human";
            break;
        case '#':
            return "Dragon";
            break;
        case '*':
            return "Monster";
            break;
        default:
            return "Empty";
            break;
        }
    }

    virtual char getSymbol() const {return '.';};
    virtual pair<int, int> getPoint() const {return make_pair(0,0);};

};


class Stone : public Entity {
    pair<int,int> point;
    public:
    pair<int,int> getPoint(){
        point = coordinate();
        return point;
    }
    char getSymbol() const { return 'S'; }
};
class Hole : public Entity {
    int depth; //= randomnumber(1, 20)
    pair<int,int> point;
    public:
    pair<int,int> getPoint(){
        point = coordinate();
        return point;
    }
    char getSymbol() const { return 'O'; }
    void setDepth(int d){
        depth = d;
    }
    int getDepth(){
        return depth;
    }
};
class Dragon : public Entity {
    int health;
    pair <int,int> point;
    pair <int,int> initialPoint;
    int depth;
    public:

    char getSymbol() const { return '#'; }

    void setHealth(int h){
        health = h;
    }
    int getHealth(){
        return health;
    }
    void reset(){
        health = 100;
    }
    void getInitialPoint(pair<int,int> coord){
        initialPoint = coord;
    }
    void useInitialPoint(){
        point = initialPoint;
    }
    pair<int,int> getPoint(){
        return point;
    }
};
class Human : public Entity {
    int health;
    string name;
    pair <int,int> point;
    pair <int,int> initialPoint;
    public:

    char getSymbol() const { return '@'; }

    int getHealth(){
        return health;
    }
    void setHealth(int h){
        health = h;
    }
    void reset(){
        health = 100;
    }
    void getInitialPoint(pair<int,int> coord){
        initialPoint = coord;
    }
    void useInitialPoint(){
        point = initialPoint;
    }
    pair<int,int> getPoint(){
        return point;
    }
    string getName(){
        return name;
    }
    void setName(int human_number){
        switch (human_number)
        {
        case 1:
            name = "Harold";
            break;
        case 2:
            name = "David";
            break;
        case 3:
            name = "Clare";
            break;
        default:
            name = "Not A Player";
        }
    }
};
class Monster : public Entity {
    int strength;
    pair <int,int> point;
    pair <int,int> initialPoint;
    int health;

    public:
    char getSymbol(){ return '*'; }
    void setHealth(int h){
        health = h;
    }
    int getHealth(){
        return health;
    }
    void reset(){
        health = 100;
    }
    void getInitialPoint(pair<int,int> coord){
        initialPoint = coord;
    }
    void useInitialPoint(){
        point = initialPoint;
    }
    pair<int,int> getPoint(){
        return point;
    }
    int getStrength(){
        return strength;
    }
    void setStrength(int s){
        strength = s;
    }

};



class Room{
    public:
    Stone stonedata;
    Hole holedata;
    Hole hole_one;
    Hole hole_two;
    Human humandata;
    Human human_one;
    Human human_two;
    Human human_three;
    Dragon dragondata;
    Dragon dragon_one;
    Dragon dragon_two;
    Monster monsterdata;
    Monster monster_one;
    Monster monster_two;
    Monster monster_three;
    char game_display[11][11];

    char stonesymbol = stonedata.getSymbol();
    //coordinate
    tuple<pair<int,int>> stone1, stone2;

    char holesymbol = holedata.getSymbol();
    //coordinate, depth
    tuple<pair<int,int>, int> hole1, hole2;

    char dragonsymbol = dragondata.getSymbol();
    //coordinate, health
    tuple<pair<int,int>, int> dragon1, dragon2;

    char humansymbol = humandata.getSymbol();
    //coordinate, name, health
    tuple<pair<int,int>, string, int> human1, human2, human3;

    char monstersymbol = monsterdata.getSymbol();
    //coordinate, strength, health
    tuple<pair<int,int>, int, int> monster1, monster2, monster3;



    
    void setRoom(){
        srand(time(NULL));
        //setting the symbols of different entities then setting the design of their coordinates
        set<pair<int, int>> usedCoordinates;
        //setting the coordinates of the entities
        int maxAttempts = 1000; // Maximum number of attempts to find unique coordinates
        int attempts = 0;
        while (true)
        {
            usedCoordinates.clear();
            stone1 = make_tuple(stonedata.getPoint());
            stone2 = make_tuple(stonedata.getPoint());

            hole_one.setDepth(randomnumber(0, 20));
            hole1 = make_tuple(holedata.getPoint(), hole_one.getDepth());
            hole_two.setDepth(randomnumber(0, 20));
            hole2 = make_tuple(holedata.getPoint(), hole_two.getDepth());

            dragon_one.setHealth(100);
            dragon1 = make_tuple(coordinate(),dragon_one.getHealth());
            dragon_two.setHealth(100);
            dragon2 = make_tuple(coordinate(),dragon_two.getHealth());

            human_one.setName(1);
            human_one.setHealth(100);
            human1 = make_tuple(coordinate(), humandata.getName(), human_one.getHealth());
            human_two.setName(2);
            human_two.setHealth(100);
            human2 = make_tuple(coordinate(), humandata.getName(), human_two.getHealth());
            human_three.setName(3);
            human_three.setHealth(100);
            human3 = make_tuple(coordinate(), humandata.getName(), human_three.getHealth());

            monster_one.setHealth(100);
            // monster_one.setStrength(randomnumber(0, 5));
            monster1 = make_tuple(coordinate(), monster_one.getHealth(), monster_one.getStrength());

            monster_two.setHealth(100);
            // monster_two.setStrength(randomnumber(0, 5));
            monster2 = make_tuple(coordinate(), monster_two.getHealth(), monster_two.getStrength());

            monster_three.setHealth(100);
            // monster_three.setStrength(randomnumber(0, 5));
            monster3 = make_tuple(coordinate(), monster_three.getHealth(), monster_three.getStrength());

            // Store all coordinates in the set and check if any duplicates exist
            usedCoordinates.insert(get<0>(stone1));
            usedCoordinates.insert(get<0>(stone2));
            usedCoordinates.insert(get<0>(hole1));
            usedCoordinates.insert(get<0>(hole2));
            usedCoordinates.insert(get<0>(dragon1));
            usedCoordinates.insert(get<0>(dragon2));
            usedCoordinates.insert(get<0>(human1));
            usedCoordinates.insert(get<0>(human2));
            usedCoordinates.insert(get<0>(human3));
            usedCoordinates.insert(get<0>(monster1));
            usedCoordinates.insert(get<0>(monster2));
            usedCoordinates.insert(get<0>(monster3));
            if (usedCoordinates.size() == 12) {break;}
            
            attempts++;
            if (attempts >= maxAttempts) {
                cout << "Error: Could not find unique coordinates within maximum attempts." << endl;
                exit(1); // Exit or handle the error appropriately
            }

        }

        dragon_one.getInitialPoint(get<0>(dragon1));
        dragon_two.getInitialPoint(get<0>(dragon2));

        human_one.getInitialPoint(get<0>(human1));
        human_two.getInitialPoint(get<0>(human2));
        human_three.getInitialPoint(get<0>(human3));

        monster_one.getInitialPoint(get<0>(monster1));
        monster_two.getInitialPoint(get<0>(monster2));
        monster_three.getInitialPoint(get<0>(monster3));
    }

    void createRoom(){
        // Creating the game display
        // j == column
        // i == row
        // k == column
        int rowvalue = 48; //The 2D char array converts it
        int columnvalue = 48;

        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                if (i == 0)
                {
                    if (j == 0)
                    {
                        game_display[i][j] = ' ';
                    }else
                    {
                        game_display[i][j] = rowvalue;
                        rowvalue+= 1;
                    }
                }else if (j == 0)
                {
                    game_display[i][j] = columnvalue;
                    columnvalue += 1;
                }else if (i == get<0>(stone1).first && j == get<0>(stone1).second || i == get<0>(stone2).first && j == get<0>(stone2).second)
                {
                    game_display[i][j] = stonesymbol;
                }else if (i == get<0>(hole1).first && j == get<0>(hole1).second || i == get<0>(hole2).first && j == get<0>(hole2).second){
                    game_display[i][j] = holesymbol;
                }else if (i == get<0>(dragon1).first && j == get<0>(dragon1).second || i == get<0>(dragon2).first && j == get<0>(dragon2).second)
                {
                    game_display[i][j] = dragonsymbol;
                }else if (i == get<0>(human1).first && j == get<0>(human1).second || i == get<0>(human2).first && j == get<0>(human2).second || i == get<0>(human3).first && j == get<0>(human3).second)
                {
                    game_display[i][j] = humansymbol;
                }else if (i == get<0>(monster1).first && j == get<0>(monster1).second || i == get<0>(monster2).first && j == get<0>(monster2).second || i == get<0>(monster3).first && j == get<0>(monster3).second)
                {
                    game_display[i][j] = monstersymbol;
                }
                
                else{game_display[i][j] = '.';}
                
                
            }
            
            
        }

    }
    Room(){
        setRoom();
        createRoom();
    }
    void updateDragonTuple(tuple<pair<int,int>, int> &tuple_name, pair<int,int> v1, int v2){
        tuple_name = make_tuple(v1, v2);
    }
    void updateHumanTuple(tuple<pair<int,int>, string, int> &tuple_name, pair<int,int> v1, string v2, int v3){
        tuple_name = make_tuple(v1, v2, v3);
    }
    void updateMonsterTuple(tuple<pair<int,int>, int, int> &tuple_name, pair<int,int> v1, int v2, int v3){
        tuple_name = make_tuple(v1, v2, v3);
    }
    void reset() {
        //Dragon
        dragon_one.useInitialPoint();
        dragon_one.reset();
        updateDragonTuple(dragon1, dragon_one.getPoint(), dragon_one.getHealth());
        dragon_two.useInitialPoint();
        dragon_two.reset();
        updateDragonTuple(dragon2, dragon_two.getPoint(), dragon_two.getHealth());

        //Human
        human_one.useInitialPoint();
        human_one.reset();
        updateHumanTuple(human1, human_one.getPoint(), human_one.getName(), human_one.getHealth());
        human_two.useInitialPoint();
        human_two.reset();
        updateHumanTuple(human2, human_two.getPoint(), human_two.getName(), human_two.getHealth());
        human_three.useInitialPoint();
        human_three.reset();
        updateHumanTuple(human3, human_three.getPoint(), human_three.getName(), human_three.getHealth());

        //Monster
        monster_one.useInitialPoint();
        monster_one.reset();
        updateMonsterTuple(monster1, monster_one.getPoint(), monster_one.getHealth(), monster_one.getStrength());
        monster_two.useInitialPoint();
        monster_two.reset();
        updateMonsterTuple(monster2, monster_two.getPoint(), monster_two.getHealth(), monster_two.getStrength());
        monster_three.useInitialPoint();
        monster_three.reset();
        updateMonsterTuple(monster3, monster_three.getPoint(), monster_three.getHealth(), monster_three.getStrength());
        createRoom();  // Reinitialize the room
    }

    pair<int,int> moveDragon(tuple<pair<int,int>, int> &dragon, Dragon &dragon_name) {
        if(dragon_name.getHealth() == -1 || dragon_name.getHealth() > 100){
            dragon_name.setHealth(100);
        }

        // cout << "Dragon Health: " << dragon_name.getHealth() << "\n";
        // Dragon moves left or right or up or down
        vector<pair<int, int>> possiblemoves = {
            {get<0>(dragon).first - 1, get<0>(dragon).second}, // Up
            {get<0>(dragon).first + 1, get<0>(dragon).second}, // Down
            {get<0>(dragon).first, get<0>(dragon).second - 1}, // Left
            {get<0>(dragon).first, get<0>(dragon).second + 1}  // Right
        };

        // Dragon moves to a random direction
        random_shuffle(possiblemoves.begin(), possiblemoves.end());

        for (auto move : possiblemoves){
            int x = move.first;
            int y = move.second;
            int dragonHealth = dragon_name.getHealth();
            if (x >= 1 && x <= 10 && y >= 1 && y <= 10 && game_display[x][y] == '.') {
                // Update the game display


                int damage = randomnumber(0, 5);
                dragonHealth = dragonHealth - damage;
                if (dragonHealth <= 0){
                    dragonHealth = 0;
                    x = get<0>(dragon).first;
                    y = get<0>(dragon).second;
                } // Ensure health doesn't go negative
                dragon_name.setHealth(dragonHealth);
                return make_pair(x,y);
                break;
                
            }
        }
        return make_pair(get<0>(dragon).first, get<0>(dragon).second);
    }
    


    pair<int,int> moveHuman(tuple<pair<int,int>, string, int> &human, Human &human_name) {
        // Human moves right
        pair<int, int> possiblemove = make_pair(get<0>(human).first, get<0>(human).second + 1);

        int x = possiblemove.first;
        int y = possiblemove.second;
        int humanHealth = human_name.getHealth();
        if (x >= 1 && x <= 10 && y >= 1 && y <= 10 && get<0>(human).second < 10 && game_display[x][y] == '.') {
            humanHealth--;
            if (humanHealth <= 0){
                humanHealth = 0;
                x = get<0>(human).first;
                y = get<0>(human).second;
                } // Ensure health doesn't go negative and entity doesn't move
            human_name.setHealth(humanHealth);
            return make_pair(x, y);
        }else if(get<0>(human).second >= 10 && x + 1 <= 10 && game_display[x+1][1] == '.'){

            humanHealth--;
            if (humanHealth <= 0) { 
                humanHealth = 0;
                x = get<0>(human).first;
                y = get<0>(human).second;
            } 
            human_name.setHealth(humanHealth);
            return make_pair(get<0>(human).first + 1, 1);
        }else{
            

            vector<pair<int, int>> lastmove = {
                {get<0>(human).first - 1, get<0>(human).second}, // Up
                {get<0>(human).first + 1, get<0>(human).second}, // Down
                {get<0>(human).first, get<0>(human).second - 1}, // Left
                {get<0>(human).first, get<0>(human).second + 1}  // Right
            };

            
            random_shuffle(lastmove.begin(), lastmove.end());

            for (auto move : lastmove){

                int x = move.first;
                int y = move.second;

                if (x >= 1 && x <= 10 && y >= 1 && y <= 10 && game_display[x][y] == '.') {


                    humanHealth--;
                    if (humanHealth < 0){
                        humanHealth = 0;
                        x = get<0>(human).first;
                        y = get<0>(human).second;
                        } 
                    human_name.setHealth(humanHealth);
                    return make_pair(x, y);
                }
            }
            
        }
        return make_pair(get<0>(human).first, get<0>(human).second);
    }

    
    pair<int,int> moveMonster(tuple<pair<int,int>, int, int> &monster, Monster &monster_name){
        monster_name.setStrength(randomnumber(0, 5));
        bool moved = false;
        int monsterStrength = monster_name.getStrength();
        int monsterHealth = monster_name.getHealth();
        vector<pair<int, int>> possiblemoves = {
            {get<0>(monster).first - monsterStrength, get<0>(monster).second}, // Up
            {get<0>(monster).first + monsterStrength, get<0>(monster).second}, // Down
            {get<0>(monster).first, get<0>(monster).second - monsterStrength}, // Left
            {get<0>(monster).first, get<0>(monster).second + monsterStrength}  // Right
        };

        random_shuffle(possiblemoves.begin(), possiblemoves.end());

        for (auto move : possiblemoves){
            int x = move.first;
            int y = move.second;

            if (x >= 1 && x <= 10 && y >= 1 && y <= 10 && game_display[x][y] == '.') {


                monsterHealth -= monsterStrength;
                if (monsterHealth <= 0){
                    monsterHealth = 0;
                    x = get<0>(monster).first;
                    y = get<0>(monster).second;
                } // Ensure health doesn't go negative
                moved = true;
                monster_name.setHealth(monsterHealth);
                return make_pair(x, y);
                break;
            }
            
        }

        if(moved == false){
            vector<pair<int, int>> lastmove = {
                {get<0>(monster).first - 1, get<0>(monster).second}, // Up
                {get<0>(monster).first + 1, get<0>(monster).second}, // Down
                {get<0>(monster).first, get<0>(monster).second - 1}, // Left
                {get<0>(monster).first, get<0>(monster).second + 1}  // Right
            };

            // Monster moves to a random direction
            random_shuffle(lastmove.begin(), lastmove.end());

            for (auto move : lastmove){
                int x = move.first;
                int y = move.second;

                if (x >= 1 && x <= 10 && y >= 1 && y <= 10 && game_display[x][y] == '.') {

                    monsterHealth--;
                    if (monsterHealth < 0){
                        monsterHealth = 0;
                        x = get<0>(monster).first;
                        y = get<0>(monster).second;
                        }
                    monster_name.setHealth(monsterHealth);
                    return make_pair(x, y);
                }
            }
        }

        //When nothing is possible
        return make_pair(get<0>(monster).first, get<0>(monster).second);
    }

    void moveAllEntities(){
        int x, y;
        pair<int,int> entitypoint;

        for (int i = 1; i < 11; i++)
        {
            for (int j = 1; j < 11; j++)
            {
                game_display[i][j] = '.';
            }
        }
        game_display[get<0>(stone1).first][get<0>(stone1).second] = stonesymbol;
        game_display[get<0>(stone2).first][get<0>(stone2).second] = stonesymbol;

        game_display[get<0>(hole1).first][get<0>(hole1).second] = holesymbol;
        game_display[get<0>(hole2).first][get<0>(hole2).second] = holesymbol;
        
        // Update positions for monsters
        pair<int,int> monster1_operation = moveMonster(monster1, monster_one);
        pair<int,int> monster2_operation = moveMonster(monster2, monster_two);
        pair<int,int> monster3_operation = moveMonster(monster3, monster_three);


        x = monster1_operation.first;
        y = monster1_operation.second;
        monster1 = make_tuple(make_pair(x, y), get<1>(monster1), get<2>(monster1));  // Update tuple with new position

        x = monster2_operation.first;
        y = monster2_operation.second;
        monster2 = make_tuple(make_pair(x, y), get<1>(monster2), get<2>(monster2));  // Update tuple with new position

        x = monster3_operation.first;
        y = monster3_operation.second;
        monster3 = make_tuple(make_pair(x, y), get<1>(monster3), get<2>(monster3));  // Update tuple with new position

        game_display[get<0>(monster1).first][get<0>(monster1).second] = monstersymbol;
        game_display[get<0>(monster2).first][get<0>(monster2).second] = monstersymbol;
        game_display[get<0>(monster3).first][get<0>(monster3).second] = monstersymbol;

        // Update positions for dragons
        pair<int,int> dragon1_operation = moveDragon(dragon1, dragon_one);
        pair<int,int> dragon2_operation = moveDragon(dragon2, dragon_two);

        x = dragon1_operation.first;
        y = dragon1_operation.second;
        dragon1 = make_tuple(make_pair(x, y), get<1>(dragon1));  // Update tuple with new position

        x = dragon2_operation.first;
        y = dragon2_operation.second;
        dragon2 = make_tuple(make_pair(x, y), get<1>(dragon2));  // Update tuple with new position

        game_display[get<0>(dragon1).first][get<0>(dragon1).second] = dragonsymbol;
        game_display[get<0>(dragon2).first][get<0>(dragon2).second] = dragonsymbol;

        //Update positions for humans
        pair<int,int> human1_operation = moveHuman(human1, human_one);
        pair<int,int> human2_operation = moveHuman(human2, human_two);
        pair<int,int> human3_operation = moveHuman(human3, human_three);

        x = human1_operation.first;
        y = human1_operation.second;
        human1 = make_tuple(make_pair(x, y), get<1>(human1), get<2>(human1));  // Update tuple with new position

        x = human2_operation.first;
        y = human2_operation.second;
        human2 = make_tuple(make_pair(x, y), get<1>(human2), get<2>(human2));  // Update tuple with new position

        x = human3_operation.first;
        y = human3_operation.second;
        human3 = make_tuple(make_pair(x, y), get<1>(human3), get<2>(human3));  // Update tuple with new position

        game_display[get<0>(human1).first][get<0>(human1).second] = humansymbol;
        game_display[get<0>(human2).first][get<0>(human2).second] = humansymbol;
        game_display[get<0>(human3).first][get<0>(human3).second] = humansymbol;
        // Print updated game display
    }
};

class Main{
    int userChoice;
    public:
    Room room;
    Entity entity;
    void display(char game_grid[11][11]){
        for (int i = 0; i < 30; i++){
            cout << '-';
        }
        cout << "\n" << "\n";
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                cout << game_grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    void run(){
        srand(time(NULL));
        while(true){
            display(room.game_display);
            cout << "\nWelcome To Mystery World" << endl;
            cout << "1." << "\t" << "Display Room" << endl;
            cout << "2." << "\t" << "Move all the animated entities" << endl;
            cout << "3." << "\t" << "Display the entity state by coordinates" << endl;
            cout << "4." << "\t" << "Reset the room" << endl;
            cout << "5." << "\t" << "Finish" << endl;
            cout << "\nEnter your numeric choice: ";
            if (cin >> userChoice) {
            }else{
                cout << "Invalid input. Please enter a numeric value.\n";
                cin.clear();
                cin.ignore(); // Discard invalid input
                continue; // Skip to the next iteration of the loop
            }
            int x;
            int y;
            if (userChoice == 1)
            {
                continue;
            }if(userChoice == 2){
                room.moveAllEntities();
            } else if (userChoice == 3)
            {
                cout << "Enter the position of that item \n";
                cout << "x: ";
                cin >> x;
                cout << "y: ";
                cin >> y;
                char entitysymbol = room.game_display[x + 1][y + 1];
                string entityname = entity.entitycheck(entitysymbol);
                cout << "\n" << "\n";
                for (int i = 0; i < 30; i++){
                    cout << '-';
                }
                cout << "\nEntity properties: \n";
                cout << "Type: " << entityname << "\n";
                if(entitysymbol == '@'){

                    //Get human coordinates
                    pair<int, int> human1_coords = get<0>(room.human1);
                    pair<int, int> human2_coords = get<0>(room.human2);
                    pair<int, int> human3_coords = get<0>(room.human3);

                    //Display name based of location

                    if (make_pair(x+1,y+1) == human1_coords){
                        string humanName = room.human_one.getName();
                        cout << "Name: " << humanName << "\n";
                    }else if (make_pair(x+1,y+1) == human2_coords){
                        string humanName = room.human_two.getName();
                        cout << "Name: " << humanName << "\n";
                    }else if (make_pair(x+1,y+1) == human3_coords){
                        string humanName = room.human_three.getName();
                        cout << "Name: " << humanName << "\n";
                    }else{
                        cout << "Name: Entity has no Name \n"; 
                    }
                } 
                if(entitysymbol == '@'){
                    pair<int, int> human1_coords = get<0>(room.human1);
                    pair<int, int> human2_coords = get<0>(room.human2);
                    pair<int, int> human3_coords = get<0>(room.human3);


                    if (make_pair(x+1,y+1) == human1_coords){
                        int human_health = room.human_one.getHealth();
                        cout << "Health: " << human_health << "\n";
                    }else if (make_pair(x+1,y+1) == human2_coords){
                        int human_health = room.human_two.getHealth();
                        cout << "Health: " << human_health << "\n";
                    }else if (make_pair(x+1,y+1) == human3_coords){
                        int human_health = room.human_three.getHealth();
                        cout << "Health: " << human_health << "\n";
                    }
                }else if(entitysymbol == '#'){
                    pair<int, int> dragon1_coords = get<0>(room.dragon1);
                    pair<int, int> dragon2_coords = get<0>(room.dragon2);


                    if (make_pair(x+1,y+1) == dragon1_coords){
                        int dragon_health = room.dragon_one.getHealth();
                        cout << "Health: " << dragon_health << "\n";
                    }else if (make_pair(x+1,y+1) == dragon2_coords){
                        int dragon_health = room.dragon_two.getHealth();
                        cout << "Health: " << dragon_health << "\n";
                    }
                }else if(entitysymbol == '*'){
                    pair<int, int> monster1_coords = get<0>(room.monster1);
                    pair<int, int> monster2_coords = get<0>(room.monster2);
                    pair<int, int> monster3_coords = get<0>(room.monster3);


                    if (make_pair(x+1,y+1) == monster1_coords){
                        int monster_health = room.monster_one.getHealth();
                        cout << "Health: " << monster_health << "\n";
                    }else if (make_pair(x+1,y+1) == monster2_coords){
                        int monster_health = room.monster_two.getHealth();
                        cout << "Health: " << monster_health << "\n";
                    }else if (make_pair(x+1,y+1) == monster3_coords){
                        int monster_health = room.monster_three.getHealth();
                        cout << "Health: " << monster_health << "\n";
                    }
                }else if(entitysymbol == 'O'){
                    pair<int, int> hole1_coords = get<0>(room.hole1);
                    pair<int, int> hole2_coords = get<0>(room.hole2);

                    if (make_pair(x+1,y+1) == hole1_coords){
                        int hole_depth = room.hole_one.getDepth();
                        cout << "Depth: " << hole_depth << "\n";
                    }else if (make_pair(x+1,y+1) == hole2_coords){
                        int hole_depth = room.hole_two.getDepth();
                        cout << "Depth: " << hole_depth << "\n";
                    }
                }
                continue;
            }else if(userChoice == 4){
                room.reset();
            }else if(userChoice == 5){
                cout << "Thanks For Playing!!\n";
                break;
            }else{
                cout << "Invalid input. Please try again.\n";
                break;
            }
        }
    }

};

int main() {
    Main Game;
    Game.run();

    return 0;
}

