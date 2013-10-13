#include "Project.h"

// ������ ����. ������ ��������� � ������� ������ ���� 128x128 ��������
const int GRID_SIZE = 384;

class TicTacToeScreen : public Screen
{
private:
    Input* input;
    Graphics* graphics;

    // ����������� ����, ��������� � �������
    Image* back;
    (Image* player)[2];

    // ������, ������������ ����, � ������� �����
    int grid[3][3], currplayer;

    void StartSettings()
    {
        // ����� ������� Graphics � Input � ������������� ��������� ����

        input = game->GetInput();
        graphics = game->GetGraphics();
        SDL_WM_SetCaption("Tic-Tac-Toe",0);
    }

    void LoadingImage()
    {
        // �������� �����������

        back = graphics->NewImage("C:\\Users\\HOME\\Desktop\\back.bmp");
        player[0] = graphics->NewImage("C:\\Users\\HOME\\Desktop\\X.bmp",255,255,255);
        player[1] = graphics->NewImage("C:\\Users\\HOME\\Desktop\\O.bmp",255,255,255);
    }

    void Reset()
    {
        // ������� ���� � ����� ����

        currplayer = 1;

        for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            grid[i][j] = 0;

        graphics->DrawImage(back,0,0);
        graphics->Flip();
    }

    int GameOver()
    {
        // -1 - ���� �� ��������; 0 - �����; 1 - �������� ��������; 2 - �������� ������

        // �������� �� ���-������ ������
        for(int i = 1; i < 3; i++)
                // �� �����������
            if( (grid[0][0] == i && grid[1][0] == i && grid[2][0] == i) ||
                (grid[0][1] == i && grid[1][1] == i && grid[2][1] == i) ||
                (grid[0][2] == i && grid[1][2] == i && grid[2][2] == i) ||

                // �� ���������
                (grid[0][0] == i && grid[0][1] == i && grid[0][2] == i) ||
                (grid[1][0] == i && grid[1][1] == i && grid[1][2] == i) ||
                (grid[2][0] == i && grid[2][1] == i && grid[2][2] == i) ||

                // �� ���������
                (grid[0][0] == i && grid[1][1] == i && grid[2][2] == i) ||
                (grid[2][0] == i && grid[1][1] == i && grid[0][2] == i) )
                return i;

        // �������� �� �����
        int count = 0;
        for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(grid[i][j] != 0)
                count++;
        // ��������� ��� ����
        if(count == 9)
            return 0;

        return -1;
    }

    void GameOverHandle(int over)
    {
        // ��������� ����� ����

        char* message;

        switch(over)
        {
        case 0:
            message = "�����! ������� ������� ��� ���?";
            break;
        case 1:
            message = "�������� ��������! ������� ������� ��� ���?";
            break;
        case 2:
            message = "������ ��������! ������� ������� ��� ���?";
            break;
        // ���� ���� �� ��������, ������������ �� �������
        default:
            return;
        }

        // ���������� ������������, ����� �� �� ������� ��� ���
        if(MessageBox(0,message,"���� ��������",MB_YESNO) == IDYES)
            Reset();
        else
            game->Exit();
    }

public:
    void Start()
    {
        StartSettings();
        LoadingImage();
        Reset();
    }

    void Update()
    {
        // ���� ����� ������� ������� � ����
        if(input->IsExit())
            game->Exit();

        // ���� ������ ����� ������ ����
        // P.S. 1 - ���, 2 - ���, 3 - ���
        if(input->IsMouseButtonDown(1))
        {
            // ����� ���������� ������� ������
            int x = input->GetButtonDownCoords().x / (GRID_SIZE / 3),
                y = input->GetButtonDownCoords().y / (GRID_SIZE / 3);

            // ���� �� ������ �� ������ ������
            if(grid[x][y] == 0)
            {
                // ������������� ������� ��� ����� � ������
                grid[x][y] = currplayer;

                if(currplayer == 1)
                    currplayer = 2;
                else
                    currplayer = 1;

                // ������ ������
                graphics->DrawImage(back,0,0);

                // ������ �������� � ������
                for(int i = 0; i < 3; i++)
                for(int j = 0; j < 3; j++)
                    if(grid[i][j] != 0)
                        graphics->DrawImage(player[ grid[i][j]-1 ], i * (GRID_SIZE / 3), j * (GRID_SIZE / 3));

                // ������� �� �����
                graphics->Flip();

                // ������������ ����� ����
                GameOverHandle(GameOver());
            }
        }
    }
};


int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
    Game game;
    return game.Execute(new TicTacToeScreen(),GRID_SIZE,GRID_SIZE);
}