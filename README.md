# Maze Learning

Game mê cung được xây dựng bằng C++ và SFML.

## Mục tiêu

Tìm hiểu cách xây dựng game 2D và các thuật toán tìm đường.

## Công nghệ

- C++
- SFML
- Visual Studio 2022

## Tiến độ

### Day 3
Ý tưởng

Nhân vật không cần class phức tạp, chỉ cần 2 con số: playerX, playerY là ô nó đang đứng. Bấm phím mũi tên thì làm 3 việc:

Tính ô muốn đi tới (newX, newY).
Hỏi: “ô đó đi được không?” (không phải tường, không ra ngoài lưới).
Nếu được thì cập nhật vị trí, không thì đứng yên.

Bước 2 là chỗ quan trọng nhất. Ta viết nó thành một hàm riêng tên isWalkable (đi được không). Sau này BFS và A* cũng dùng đúng hàm này để hỏi “từ ô này đi sang ô hàng xóm được không”.