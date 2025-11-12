<h1>📘 STM32 Scheduler Project - LAB 4</h1>
  <p><strong>Mục tiêu:</strong> Xây dựng bộ lập lịch (Scheduler) thay thế cho việc sử dụng nhiều timer trong dự án STM32, 
  nhằm quản lý đa tác vụ định kỳ như nhấp nháy LED, đọc nút nhấn, xử lý tín hiệu mà không gây xung đột ngắt.</p>

  <h2>🧩 1. Giới thiệu</h2>
  <p>Dự án sử dụng <strong>Scheduler</strong> chạy trên <strong>STM32F103C6</strong> để quản lý các tác vụ theo thời gian thực.
  Thay vì dùng nhiều timer hardware, hệ thống chỉ dùng một timer (ví dụ TIM2) để gọi hàm <code>SCH_Update()</code> định kỳ mỗi tick (1 ms).</p>

  <h3>Ưu điểm</h3>
  <ul>
    <li>Giảm số lượng ngắt phần cứng sử dụng.</li>
    <li>Dễ dàng thêm/bớt các tác vụ bằng cách gọi <code>SCH_AddTask()</code>.</li>
    <li>Đảm bảo độ ổn định khi chạy nhiều LED, nút nhấn hoặc sensor song song.</li>
  </ul>

  <h2>🚀 2. Cách hoạt động</h2>
  <p>Scheduler duy trì một danh sách tác vụ được sắp xếp theo <code>delay</code> (thời gian chờ ban đầu). 
  Mỗi tick timer (ví dụ 1 ms), hàm <code>SCH_Update()</code> được gọi để giảm delay của task đầu tiên. 
  Khi task có delay = 0, nó được chuyển sang hàng đợi ready để thực thi trong <code>SCH_Dispatch_Tasks()</code>.</p>

  <h3>Ví dụ</h3>
 

SCH_Init();
SCH_AddTask(leda,   0,  500);
SCH_AddTask(ledb,   0, 1000);
SCH_AddTask(ledc,   0, 1500);
SCH_AddTask(ledd,   0, 2000);
SCH_AddTask(lede,   0, 2500);
SCH_AddTask(ledf,3000,    0);
SCH_AddTask(button, 10, 1000);

while(1){
  SCH_Dispatch_Tasks();
}</code></pre>

  <h3>Giải thích:</h3>
  <ul>
    <li><code>leda</code> → nhấp nháy mỗi 500ms.</li>
    <li><code>ledb</code> → nhấp nháy mỗi 1000ms.</li>
    <li><code>ledf</code> → chạy 1 lần duy nhất sau 3s.</li>
    <li><code>button</code> → đọc nút mỗi 1000ms, nếu giữ lâu thì toggle LED0.</li>
  </ul>

  <h2>🧮 3. Tham số <code>delay</code> và <code>period</code></h2>
  <ul>
    <li><strong>delay:</strong> thời gian chờ trước khi task đầu tiên chạy (tính theo đơn vị tick).</li>
    <li><strong>period:</strong> chu kỳ lặp lại; nếu =0 → task chỉ chạy một lần.</li>
  </ul>


  <h2>👤 4. Tác giả</h2>
  <ul>
    <li><strong>Họ tên:</strong> Hồng Phi Trường</li>
    <li><strong>Ngày thực hiện:</strong> 2025</li>
    <li><strong>Ngôn ngữ:</strong> C (STM32 HAL Library)</li>
  </ul>

  <footer>
    © 2025 Hồng Phi Trường — STM32 Scheduler Project
  </footer>

</body>
