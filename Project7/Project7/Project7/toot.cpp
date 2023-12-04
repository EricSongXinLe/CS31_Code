// gas.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get City::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXTOOTERS = 125;           // max number of Tooters allowed

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class City;  // This is needed to let the compiler know that City is a
             // type name, since it's mentioned in the Tooter declaration.

class Tooter
{
  public:
        // Constructor
    Tooter(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};

class Player
{
  public:
        // Constructor
    Player(City *cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;

        // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_age;
    int   m_health;
      // You'll probably find that a player object needs an additional
      //       data member to support your implementation of the behavior
      //       affected by the player's being blasted with gas.
};

class City
{
  public:
        // Constructor/destructor
    City(int nRows, int nCols);
    ~City();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    bool    isPlayerAt(int r, int c) const;
    int     tooterCount() const;
    int     nTootersAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

        // Mutators
    bool addTooter(int r, int c);
    bool addPlayer(int r, int c);
    void preachToTootersAroundPlayer();
    void moveTooters();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Tooter* m_tooters[MAXTOOTERS];
    int     m_nTooters;

      // Helper functions
    bool isInBounds(int r, int c) const;
};

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nTooters);
    ~Game();

        // Mutators
    void play();

  private:
    City* m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Tooter implementation
///////////////////////////////////////////////////////////////////////////

Tooter::Tooter(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** A Tooter must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "***** Tooter created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Tooter::row() const
{
    return m_row;
}

int Tooter::col() const
{
    // TRIVIAL:  Return the column the Tooter is at.
    return m_col;
}

void Tooter::move()
{
      // Attempt to move in a random direction; if it can't move, don't move.
      // If the player is there, don't move.
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
    if(dir == UP){
        if(row()-1 != ((m_city->player())->row())){
            m_city->determineNewPosition(m_row,m_col,dir);
        }
    }
    else if(dir == DOWN){
        if(row()+1 != ((m_city->player())->row())){
            m_city->determineNewPosition(m_row,m_col,dir);
        }
    }
    else if(dir == LEFT){
        if(col()-1 != ((m_city->player())->col())){
            m_city->determineNewPosition(m_row,m_col,dir);
        }
    }
    else if(dir == RIGHT){
        if(col()+1 != ((m_city->player())->col())){
            m_city->determineNewPosition(m_row,m_col,dir);
        }
    }
    //Move in the appropriate direction if allowed
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_health = 12;
      // You might or might not put something here.
}

int Player::row() const
{
    // TRIVIAL:  Return the row the player is at.
    return m_row;
}

int Player::col() const
{
    // TRIVIAL:  Return the column the player is at.
    return m_col;
}

int Player::age() const
{
    // TRIVIAL:  Return the player's age.
    return m_age;
}

int Player::health() const
{
    // TRIVIAL:  Return the player's health status.
    return m_health;
}

bool Player::isPassedOut() const
{
    if(m_health > 0 ){
        return false;
    }
    //TRIVIAL:  Return whether the player is passed out.
    return true;
}

void Player::preach()
{
    m_age++;
    m_city->preachToTootersAroundPlayer();
}

void Player::move(int dir)
{
    m_age++;
    if(dir == UP){
        if((m_city->nTootersAt(row()-1, col()))==0){
            m_row--; //move
        }
    }
    else if(dir == DOWN){
        if((m_city->nTootersAt(row()+1, col()))==0){
            m_row++; //move
        }
    }
    else if(dir == LEFT){
        if((m_city->nTootersAt(row(), col()-1))==0){
            m_col--; //move
        }
    }
    else if(dir == RIGHT){
        if((m_city->nTootersAt(row(), col()+1))==0){
            m_col++; //move
        }
    }
      // If there is a grid position in the indicated direction that is
      //        adjacent to the player and vacant, move the player there;
      //        otherwise, don't move.
}

void Player::getGassed()
{
    m_health--;
    //TRIVIAL
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** City created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nTooters = 0;
}

City::~City()
{
    delete m_player;
    for(int i =0;i<tooterCount();i++){
        delete m_tooters[i];
    }
    // Delete the player and all remaining dynamically allocated Tooters.
}

int City::rows() const
{
    // TRIVIAL:  Return the number of rows in the city.
    return m_rows;
}

int City::cols() const
{
    // TRIVIAL:  Return the number of columns in the city.
    return m_cols;
}

Player* City::player() const
{
    return m_player;
}

bool City::isPlayerAt(int r, int c) const
{
    //Return true if the player is at row r, column c, otherwise false.
    if((r == (m_player->row()))&&(c == (m_player->col()))){
        return true;
    }
    return false;  // This implementation compiles, but is incorrect.
}

int City::tooterCount() const
{
    return m_nTooters;
}

int City::nTootersAt(int r, int c) const
{
    int count = 0;
    // Return the number of Tooters at row r, column c.
    for(int i =0; i<(this->tooterCount());i++){
        if((c==m_tooters[i]->col()) && (r == m_tooters[i]->row())){
            count++;
        }
    }
    return count;
}

bool City::determineNewPosition(int& r, int& c, int dir) const
{
      // If a move from row r, column c, one step in direction dir
      //        would go off the edge of the city, leave r and c unchanged and
      //        return false.  Otherwise, set r or c so that row r, column c,
      //        is now the new position resulting from the proposed move, and
      //        return true.
    switch (dir)
    {
      case UP:
            if(isInBounds(r-1, c)){
                r--;
            }
        // Implement the behavior if dir is UP.
            break;
      case DOWN:
            if(isInBounds(r+1, c)){
                r++;
            }
            break;
      case LEFT:
            if(isInBounds(r, c-1)){
                c--;
            }
            break;
      case RIGHT:
            if(isInBounds(r, c+1)){
                c++; //C++! woohoo!
            }
        // :  Implement the other directions.
            break;
      default:
        return false;
    }
    return true;
}

void City::display() const
{
      // Position (row,col) in the city coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c = 0;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each Tooter's position
    // If one Tooter is at some grid point, set the char to 'T'.
    int tooterNum;
    for(int i =0; i<tooterCount();i++){
        tooterNum = nTootersAt(m_tooters[i]->row(),m_tooters[i]->col());
        switch(tooterNum){
            case 1:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = 'T';
                break;
            case 2:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '2';
                break;
            case 3:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '3';
                break;
            case 4:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '4';
                break;
            case 5:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '5';
                break;
            case 6:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '6';
                break;
            case 7:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '7';
                break;
            case 8:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '8';
                break;
            case 9:
                grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '9';
                break;
        }
        if(tooterNum>9){
            grid[m_tooters[i]->row()-1][m_tooters[i]->col()-1] = '9';
        }
    }
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.

        // Indicate player's position
    if (m_player != nullptr)
    {
          // Set the char to '@', unless there's also a Tooter there
          // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, Tooter, and player info
    cout << "There are " << m_nTooters << " unconverted Tooters remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addTooter(int r, int c)
{
    if (! isInBounds(r, c))
        return false;

      // Don't add a Tooter on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if(MAXTOOTERS == tooterCount()){
        return false;
    }
    m_tooters[tooterCount()] = new Tooter(this, r,c);
    m_nTooters++;
      // If there are MAXTOOTERS unconverted Tooters, return false.
      // Otherwise, dynamically allocate a new Tooter at coordinates (r,c).
      // Save the pointer to the newly allocated Tooter and return true.

      // Your function must work as specified in the preceding paragraph even
      // in this scenario (which won't occur in this game):  MAXTOOTERS
      // Tooters are added, then some are converted and removed from the city,
      // then more are added.

      // Implement this.
    return true;  // This implementation compiles, but is incorrect.
}

bool City::addPlayer(int r, int c)
{
    if (! isInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a Tooter
    if (nTootersAt(r, c) > 0)
        return false;

      // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

bool isDiagAdj(const int rp, const int cp, const int rt, const int ct){
    if((rp-1 == rt) && (cp-1 == ct)){
        return true;
    }
    else if((rp+1 == rt) && (cp-1 == ct)){
        return true;
    }
    else if((rp-1 == rt) && (cp+1 == ct)){
        return true;
    }
    else if((rp+1 == rt) && (cp+1 == ct)){
        return true;
    }
    return false;
}

bool isOrthoAdj(const int rp, const int cp, const int rt, const int ct){
    if((rp - 1 == rt) && (cp == ct)){
        return true;
    }
    else if((rp + 1 == rt) && (cp == ct)){
        return true;
    }
    else if((rp == rt) && (cp+1 == ct)){
        return true;
    }
    else if((rp == rt) && (cp -1 == ct)){
        return true;
    }
    return false;
}

void City::preachToTootersAroundPlayer()
{
    int rp, cp, rt, ct, rndInt;
    rp = m_player->row();
    cp = m_player->col();
    for(int i = 0; i< m_nTooters; i++){
        rt = m_tooters[i]->row();
        ct = m_tooters[i]->col();
        if(isDiagAdj(rp, cp, rt, ct) || isOrthoAdj(rp, cp, rt, ct)){
            rndInt = randInt(1,3);
            if (rndInt == 1 || rndInt == 2){
                delete m_tooters[i];
                for(int j=i;j<m_nTooters-1;j++){
                    m_tooters[j] = m_tooters[j+1];
                }
                m_nTooters--;
            }
        }
    }
      // Preach to Tooters orthogonally or diagonally adjacent to player.
      // If a Tooter is converted, destroy it and remove it from the city,
      // since we have no further need to display it or have it interact with
      // the player.

      // Implement this.
}

void City::moveTooters()
{
    for (int k = 0; k < m_nTooters; k++)
    {
        m_tooters[k]->move();
      // Have the k-th Tooter in the city make one move.
      //        If that move results in that Tooter being orthogonally
      //        adjacent to the player, the player suffers a gas blast.
        int rp, cp, rt, ct;
        rp = m_player->row();
        cp = m_player->col();
        rt = m_tooters[k]->row();
        ct = m_tooters[k]->col();
        if(isOrthoAdj(rp, cp, rt, ct)){
            m_player->getGassed();
        }
    }
}

bool City::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nTooters)
{
    if (nTooters < 0)
    {
        cout << "***** Cannot create Game with negative number of Tooters!" << endl;
        exit(1);
    }
    if (nTooters > MAXTOOTERS)
    {
        cout << "***** Trying to create Game with " << nTooters
             << " Tooters; only " << MAXTOOTERS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nTooters > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the Tooters!" << endl;
        exit(1);
    }

        // Create city
    m_city = new City(rows, cols);

        // Add a player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_city->addPlayer(rPlayer, cPlayer);

      // Populate with Tooters
    while (nTooters > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
          // Don't put a Tooter where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_city->addTooter(r, c);
        nTooters--;
    }
}

Game::~Game()
{
    delete m_city;
}

void Game::play()
{
    m_city->display();
    Player* p = m_city->player();
    if (p == nullptr)
        return;

    while ( ! p->isPassedOut()  &&  m_city->tooterCount() > 0)
    {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player preaches
            p->preach();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                p->move(decodeDirection(action[0]));
                break;
            }
        }
        m_city->moveTooters();
        m_city->display();
    }
    if (p->isPassedOut())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

  // Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rdv;
    static default_random_engine generator(rdv());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32  //  Windows

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Windows

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
