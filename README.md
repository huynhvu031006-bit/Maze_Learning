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

BFS đếm số bước. Dijkstra cộng chi phí: ô đất thường tốn 1, ô bùn tốn 10. Xét mê cung nhỏ này, đi từ S tới G:

#######
#S.M.G#
#.###.#
#.....#
#######
Đường trên (qua bùn M): 4 bước, chi phí 1 + 10 + 1 + 1 = 13.
Đường dưới (vòng xuống): 8 bước, chi phí 8.

BFS chọn đường trên vì ít bước hơn. Dijkstra chọn đường dưới vì rẻ hơn.

Dijkstra giống BFS, chỉ đổi 2 chỗ:

queue đổi thành priority queue: lấy ra ô có tổng chi phí nhỏ nhất trước, thay vì ô vào sớm nhất.
Mỗi ô nhớ thêm “đi tới đây tốn tổng cộng bao nhiêu” (gọi là dist).