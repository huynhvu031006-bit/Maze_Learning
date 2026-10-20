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

DFS giống con chuột chũi: đào một mạch dài, bí thì mới lùi.

Prim giống vết mực loang: bắt đầu từ một chấm nhỏ, rồi loang dần ra xung quanh, ở chỗ nào cũng được, không đi một mạch.

Cách làm:

Đào ô (1,1) làm điểm xuất phát.
Ghi vào một danh sách biên (frontier) những ô tường cách mép vùng đã đào đúng 2 bước. Đây là “những chỗ có thể loang tới”.
Bốc ngẫu nhiên một ô bất kỳ trong danh sách biên.
Ô đó đang kề với vùng đã đào. Chọn một ô đã đào bên cạnh nó, đục bức tường ở giữa để nối lại, rồi biến ô đó thành đường.
Thêm các ô tường mới xung quanh nó vào danh sách biên.
Lặp lại cho đến khi danh sách biên rỗng.


