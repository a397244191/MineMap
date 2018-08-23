# 踩地雷小遊戲
使用語言：C++
環境：windows7
IDE：Qt Creator
UI相關來源：Qt
## 功能介紹

### 選單
左上角Restart為一個選單有三個選項Large,Medium,Small分別是重新開始一個大、中、小的遊戲
- 大小介紹
  - 大遊戲畫面為$16*30$有99個地雷
  - 中遊戲畫面為$16*16$有40個地雷
  - 小遊戲畫面為$9*9$有10個地雷

### 遊玩方式
地雷圖有數個按鈕，分別對它按下滑鼠左右鍵會打開和標記按鈕
- 操作功能
  - 滑鼠左鍵
    - 打開位置
      - 打開該位置
  - 滑鼠右鍵
    - 未標記
      - 標記位置，按鈕顯示O
    - 已標記
      - 取消標記，按鈕的O顯示消失
### 額外功能
- 顯示
  - 對於附近(9宮格內)有地雷的非地雷位置
    - 顯示數字來表示附近地雷數目
  - 地雷本身
    - 顯示X
- 幫助
  - 附近(9宮格內)無地雷的非地雷位置
    - 幫助展開9宮格所有格子(必定都沒地雷)
## 畫面

遊玩畫面
![](https://i.imgur.com/ctwY4PD.png)
重新開始列表
![](https://i.imgur.com/OEKl5Kt.png)
結束畫面
Congralation
![](https://i.imgur.com/q7tkIIb.png)

Game Over
![](https://i.imgur.com/4y0ioh1.png)

其他大小顯示
中

![](https://i.imgur.com/HJAJ7eh.png)

小
![](https://i.imgur.com/jqsiQfO.png)
