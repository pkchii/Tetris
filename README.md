# TETRIS
*Bài tập cuối kì học phần Lập trình nâng cao - INT2215* 
- Tên sinh viên: Phạm Kim Chi
- MSV: 21020287
## Mô tả chung về trò chơi:
- Đây là trò chơi Tetris cổ điển. Mục tiêu của trò chơi là di chuyển các khối gạch đang rơi từ từ xuống trong kích thước bảng hình chữ nhật 20 hàng x 10 cột. Chỗ nào có hình rồi thì không di chuyển được tới vị trí đó. Người chơi xếp những khối hình sao cho khối hình lấp đầy 1 hàng ngang để ghi điểm và hàng ngang ấy sẽ biến mất.
- Người chơi sử dụng bàn phím để chơi:
  + Nhấn các phím mũi tên Down, Left, Right để di chuyển các khối hình
  + Nhấn phím mũi tên Up để xoay khối hình
  + Nhấn phím Space để ném khối hình
  + Nhấn phím LShift hoặc c để giữ lại khối hình
  + Nhấn phím q để thoát trò chơi
  + Nhấn phím a để chơi lại sau khi game đã kết thúc
- Người chơi di chuyển các khối hình lấp đầy các hàng ngang để ghi điểm.
- Trong lúc chơi, có thể tạm dừng hoặc thoát trò chơi, khi thoát sẽ ghi nhận số điểm hiện tại của người chơi.
## Các ý tưởng chính:
- Quản lí các khối hinh và bảng chơi bằng ma trận
- Tạo ngẫu nhiên các loại khối hình ở trên cùng bảng và cho chúng di chuyển xuống dưới
- Mỗi khi người chơi nhấn phím di chuyển hoặc ném sẽ kiểm tra va chạm giữa khối hình và phần hình có sẵn trên bảng. Kiểm tra va chạm bằng cách truy xuất các phần tử của bảng và của khối hình.
- Khi một hàng ngang của bảng được lấp đầy sẽ xoá hàng ngang đó và di chuyển các hàng ngang bên trên xuống, điểm được tính theo số hàng đã xoá
- Điểm càng cao tốc độ rơi các khối hình càng nhanh
- Trò chơi kết thúc khi khối hình mới tạo ra va chạm với khối hình trên bảng.
## Các chức năng đã cài đặt:
- Menu của game: chơi game, xem bảng điểm cao, thoát khỏi game
- Bảng điểm cao: hiển thị 5 số điểm cao nhất của trò chơi
- Âm thanh khi chơi và các hiệu ứng có thể bật/tắt tuỳ ý
- Tạm dừng/tiếp tục trong khi chơi hoặc quay trở lại menu
- Nhận input từ chuột để chọn các lựa chọn
- Nhận input từ bàn phím để di chuyển hoặc xoay khối hình
- Tính điểm và in ra điểm sau mỗi lượt chơi, số điểm cao nhất hiện tại
- Chơi lại nhiều lần/thoát game
- Lưu điểm khi trò chơi kết thúc hoặc khi người chơi chủ động thoát trò chơi
### [Link demo](https://youtu.be/w9TxHudA7ww)

## Các kĩ thuật lập trình đã sử dụng:
*Game sử dụng ngôn ngữ C/C++*
- Mảng tĩnh
- Mảng động vector
- Con trỏ
- Đồ họa, âm thanh SDL
- Xâu
- Sắp xếp
- Đọc, ghi tệp
- Class

## Hướng phát triển:
- Thêm nhiều khối hình hơn.
- Thêm chức năng chọn mức độ khó của trò chơi.
- Thêm chức năng tài khoản.
- Tạo game nhiều người chơi:
  + Người chơi là đồng đội của nhau: tạo bảng có kích thước lớn hơn để người chơi cùng nhau xếp các khối hình.
  + Người chơi là đối thủ của nhau: tạo hai bảng cho hai người chơi riêng biệt, xét thắng thua theo số điểm cuối cùng.
  + Khi đó, lưu bảng điểm theo các chế độ chơi riêng biệt.
- Phát triển thành game online khi có đủ kiến thức và kĩ năng cần thiết:
  + Người chơi có thể chơi cùng nhau cùng một thời điểm trên các thiết bị khác nhau.
  + Sử dụng database lưu lại tất cả dữ liệu của người chơi và khai thác chúng (tên, lượt chơi, số điểm từng lượt, số điểm trung bình, xếp hạng số điểm, xếp hạng người chơi,...)
  + Bổ sung phần nhiệm vụ hằng ngày và có những thử thách cho người chơi tham gia để thu hút người chơi chơi game nhiều hơn.
### [Phiên bản AI](https://github.com/pkchii/Tetris_SimpleAI)
## Kết luận:
- Đây là một game kinh điển, không có quá nhiều thuật toán phức tạp tuy nhiên khi thực sự bắt tay vào làm em/mình mới thấy bản thân còn thiếu sót rất rất nhiều.
  + Đồ hoạ chưa được đẹp mắt, âm thanh còn sơ sài.
  + Code còn dài dòng và tối nghĩa khi em/mình chưa kịp học hết về lập trình hướng đối tượng.
  + Trong quá trình làm em/mình gặp rất nhiều lỗi về phần con trỏ và bộ nhớ vì chưa hiểu thấu đáo.
  + Khởi đầu rất khó khăn vì chỉ với việc cài đặt SDL2 thôi em/mình đã phải nghiên cứu mất hơn 1 tuần vì chưa hiểu về cách liên kết thư viện.
  + Khi bắt đầu code, mình phải tham khảo rất nhiều source code mới có thể hiểu logic trò chơi và cách quản lí các đối tượng.
- Về những điều tâm đắc của bản thân:
  + Đây là dự án hoàn thiện đầu tiên của em/mình. Trong quá trình làm em/mình đã có thêm những hiểu biết về quy trình thực hiện project, không thể chỉ ngồi xuống và code thôi như cách em/mình đã làm trước đây được.
  + Trong thời gian làm dự án, bởi vì gặp nhiều lỗi như vậy, nên em/mình phát hiện ra những khuyết điểm của bản thân, và cũng nhờ quá trình này kĩ năng code của em/mình đã tiến bộ hơn rất nhiều.
  + Em/mình còn có cơ hội học thêm về đồ hoạ SDL, lập trình hướng đối tượng. Dù không kịp thời gian để khai thác hết các lĩnh vực này nhưng em cũng đã có thêm được những kiến thức bổ ích.
- Trước đây, em/mình chưa từng có ý định sẽ đi theo định hướng lập trình game vì nghĩ nó sẽ khó khăn và không phù hợp với mình. Nhưng hiện tại, em/mình đã có cái nhìn khác đi và sẽ không tự giới hạn bản thân ở bất kì lĩnh vực nào. Đó là điều ý nghĩa nghĩa nhất mà em/mình có được sau dự án này.
- Em/mình rất mong được các thầy và các bạn góp ý, chỉ dẫn để hoàn thiện dự án này hơn nữa.

## Hướng dẫn cài đặt trên Window:
- Cách 1: Clone repository về máy và mở file Tetris.sln trên Visual Studio
- Cách 2: Tải tại phần Release và giải nén sau đó mở file setup.exe và làm theo hướng dẫn

*Trong trường hợp có vấn đề cần thắc mắc, liên hệ với mình qua email 21020287@vnu.edu.vn*

## Nguồn code, hình ảnh và âm thanh
 - Em/mình học về SDL2 tại [lazyfool](https://lazyfoo.net/tutorials/SDL/)
 - Phần logic game em/mình tham khảo của [javilop](https://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/)
 - Phần source code em/mình tham khảo [Pixeltetris 0.2.0](https://github.com/jumpmanmv/pixeltetris/releases), tự code lại phần menu, pause và bổ sung các tính năng highscore, âm thanh, đồ hoạ.
 - Phần hình ảnh em/mình chủ yếu lấy từ source code rồi chỉnh sửa lại, một số hình ảnh khác tìm trên google.
 - Phần âm thanh em/mình lấy từ [đây](https://lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php) và một số khác từ google.
