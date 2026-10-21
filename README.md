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

Hãy tưởng tượng bạn thả một giọt nước vào mê cung ở chỗ nhân vật đứng. Nước loang đều ra mọi hướng cùng lúc: lan 1 bước, rồi 2 bước, rồi 3 bước... Giọt nước chạm ô đích ở bước thứ mấy thì đó là số bước ngắn nhất.

Queue (hàng đợi) giống xếp hàng mua vé: ai đến trước được phục vụ trước. Nhờ vậy các ô gần điểm xuất phát luôn được xử lý trước các ô xa.

Các bước của BFS:
Cho ô xuất phát vào hàng đợi, đánh dấu “đã thăm”.
Lấy ô ở đầu hàng ra.
Nếu là ô đích: xong.
Nếu không, xét 4 hàng xóm. Hàng xóm nào đi được (isWalkable) và chưa thăm thì đánh dấu đã thăm, ghi nhớ “tôi đến từ ô nào”, rồi cho vào cuối hàng.
Lặp lại từ bước 2.