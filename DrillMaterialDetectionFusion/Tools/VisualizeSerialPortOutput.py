import sys
import serial
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget
from PyQt5.QtCore import QTimer, Qt
from PyQt5.QtGui import QColor
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from collections import defaultdict, deque

# グラフを描画するウィジェット
class PlotCanvas(FigureCanvasQTAgg):
    def __init__(self, parent=None):
        self.fig, self.ax = plt.subplots()
        super().__init__(self.fig)
        self.setParent(parent)
        self.ax.set_title("DEEPCRAFT Drill Material Detection Demo")
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Scores (0.0 - 1.0)")
        self.ax.set_xlim(0, 50)  # デフォルトの表示範囲（スクロールのために動的に更新）
        self.ax.set_ylim(0, 1.0)
        self.data = defaultdict(lambda: deque(maxlen=50))  # ラベル別にデータを保存

        self.colors = {}  # ラベルごとの色を格納

    def update_plot(self):
        self.ax.clear()
        self.ax.set_title("DEEPCRAFT Drill Material Detection Demo")
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Scores (0.0 - 1.0)")
        #self.ax.set_xlim(0, len(next(iter(self.data.values()), [])) + 10)
        self.ax.set_xlim(0, len(next(iter(self.data.values()), [])))
        self.ax.set_ylim(-0.01, 1.01)

        for label, scores in self.data.items():
            if label not in self.colors:
                self.colors[label] = plt.cm.tab10(len(self.colors) % 10)

            self.ax.plot(list(range(len(scores))), scores, label=label, color=self.colors[label])

        self.ax.legend(loc="upper left")
        self.draw()

    def add_data(self, label, score):
        self.data[label].append(score)


# メインウィンドウクラス
class MainWindow(QMainWindow):
    def __init__(self, serial_port):
        super().__init__()
        self.serial_port = serial_port

        # UIの設定
        self.init_ui()

        # タイマーを設定して定期的にデータを取得
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.read_serial_data)
        self.timer.start(10)  # 10msごとにデータの読み込みを行う

    def init_ui(self):
        self.setWindowTitle("Drill Material Detection Serial Data Monitor")
        self.setGeometry(100, 100, 640, 480)

        # メインウィジェット
        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        # ラベル用レイアウト
        self.label_layout = QVBoxLayout()

        # 折れ線グラフ用キャンバス
        self.plot_canvas = PlotCanvas(self)

        # メインレイアウト
        main_layout = QVBoxLayout()
        main_layout.addLayout(self.label_layout)
        main_layout.addWidget(self.plot_canvas)

        self.central_widget.setLayout(main_layout)

    def read_serial_data(self):
        try:
            while self.serial_port.in_waiting > 0:  # バッファの中にデータがある限り
            #if self.serial_port.in_waiting > 0:
                data = self.serial_port.readline().decode('utf-8').strip()
                if not data.startswith("DATA"):
                    return

                parts = data.split(',')
                data_pairs = parts[1:]  # "DATA"部分を除去

                labels_and_scores = {}
                for i in range(0, len(data_pairs), 2):
                    label = data_pairs[i]
                    score = float(data_pairs[i + 1])
                    labels_and_scores[label] = score

                self.update_ui(labels_and_scores)
                self.update_plot(labels_and_scores)

        except Exception as e:
            print(f"Error reading serial data: {e}")

    def update_ui(self, labels_and_scores):
        # ラベル表示部分のクリア
        for i in range(self.label_layout.count()):
            widget = self.label_layout.itemAt(i).widget()
            if widget:
                widget.deleteLater()

        # スコアが最大のラベルを取得
        max_label = max(labels_and_scores, key=labels_and_scores.get)
        max_score = labels_and_scores[max_label]

        # ラベルとスコアを表示
        for label, score in labels_and_scores.items():
            color = QColor(255, 0, 0) if label == max_label else QColor(0, 0, 0)
            label_widget = QLabel(f"{label}: {score:.2f}")
            label_widget.setStyleSheet(f"color: {color.name()}; font-size: 16px;")
            label_widget.setAlignment(Qt.AlignLeft)
            self.label_layout.addWidget(label_widget)

    def update_plot(self, labels_and_scores):
        for label, score in labels_and_scores.items():
            self.plot_canvas.add_data(label, score)

        self.plot_canvas.update_plot()


# メイン関数
def main():
    app = QApplication(sys.argv)

    # シリアルポートの設定
    try:
        serial_port = serial.Serial('COM3', baudrate=115200, timeout=1)  # ポートを適切に設定
        serial_port.flushInput()  # 起動時にバッファをフラッシュ
        while serial_port.in_waiting > 0:  # バッファの中にデータがある限り
            data = serial_port.readline().decode('utf-8').strip()
    except Exception as e:
        print(f"Error opening serial port: {e}")
        sys.exit(1)

    window = MainWindow(serial_port)
    window.show()
    app.exec_()


if __name__ == "__main__":
    main()