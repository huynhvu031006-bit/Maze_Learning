# Maze Learning

Game mê cung được xây dựng bằng C++ và SFML.

## Mục tiêu

Tìm hiểu cách xây dựng game 2D và các thuật toán tìm đường.

## Công nghệ

- C++
- SFML
- Visual Studio 2022

## Tiến độ

### Day 6
Ý tưởng

Dọn nhà

main ôm quá nhiều code 
sau khi dọn còn 
main () 
{
    game game1;
    game1.run();
    return 0;
}

và game.hpp chia thành các hàm nhỏ có tên rõ ràng.
game()
run();
handleEvents();
handleKey();
updat();
render();
newMaze();
resetSearch(), showStats();