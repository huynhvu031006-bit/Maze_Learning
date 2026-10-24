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

Dijkstra giống giọt nước loang đều ra mọi hướng. Nó chỉ biết “đã đi tốn bao nhiêu” nên cứ mở rộng ô rẻ nhất, kể cả ô nằm ngược hướng với đích.

A* thêm một “cái la bàn”: ước lượng “từ ô này tới đích còn khoảng bao xa”. Nó ưu tiên ô vừa rẻ vừa có vẻ gần đích.
Mỗi ô có 3 con số:

Ký hiệu	       Ý nghĩa	                                                                     Ví dụ lái xe
g	           chi phí đã đi từ xuất phát tới ô này (đúng như dist của Dijkstra)	         đã chạy 20 km
h	           ước lượng chi phí còn lại tới đích                                          	còn cách đích 5 km theo đường chim bay
f = g + h	   tổng ước lượng của cả hành trình                                            	dự kiến 25 km

A* luôn lấy ra ô có f nhỏ nhất. Dijkstra chính là A* khi h = 0 (không có la bàn).