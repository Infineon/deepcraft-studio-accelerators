import sys
import serial
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget
from PyQt5.QtCore import QTimer, Qt
from PyQt5.QtGui import QColor
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from collections import defaultdict, deque

# Widget for drawing graphs
class PlotCanvas(FigureCanvasQTAgg):
    def __init__(self, parent=None):
        self.fig, self.ax = plt.subplots()
        super().__init__(self.fig)
        self.setParent(parent)
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Scores (0.0 - 1.0)")
        self.ax.set_xlim(0, 50)  # Default time range
        self.ax.set_ylim(0, 1.0)
        self.data = defaultdict(lambda: deque(maxlen=50))  # Data Storage by Label
        self.colors = {}  # ラベル別色

    def update_plot(self):
        self.ax.clear()  # Clear the previous graph
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Scores (0.0 - 1.0)")
        self.ax.set_xlim(0, 50)
        self.ax.set_ylim(-0.01, 1.01)
        # Plot graphs using label data and color
        for label, scores in self.data.items():
            if label not in self.colors:
                self.colors[label] = plt.cm.tab10(len(self.colors) % 10)
            self.ax.plot(list(range(len(scores))), scores, label=label, color=self.colors[label])
        self.ax.legend(loc="upper left")
        self.draw()

    def add_data(self, label, score):
        self.data[label].append(score)


# Main Window Class
class MainWindow(QMainWindow):
    def __init__(self, serial_port):
        super().__init__()
        self.serial_port = serial_port
        self.init_ui()
        # Timer (for serial data reading)
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.read_serial_data)
        self.timer.start(10)  # Acquire data at 10ms intervals

    def init_ui(self):
        self.setWindowTitle("DEEPCRAFT Drill Material Detection Demo")
        self.setGeometry(100, 100, 640, 480)
        self.setMinimumSize(320, 240)
        # Main widget
        self.central_widget = QWidget(self)
        self.setCentralWidget(self.central_widget)

        # title label
        self.title_label = QLabel("DEEPCRAFT Drill Material Detection Demo")
        self.title_label.setStyleSheet("font-size: 60px; font-weight: bold;")
        self.title_label.setAlignment(Qt.AlignCenter)

        # Label Layout
        self.label_layout = QVBoxLayout()

        # Graph canvas
        self.plot_canvas = PlotCanvas(self)

        # Main Layout
        main_layout = QVBoxLayout()
        main_layout.addWidget(self.title_label)
        main_layout.addLayout(self.label_layout)
        main_layout.addWidget(self.plot_canvas, stretch=1)
        self.central_widget.setLayout(main_layout)

        main_layout.setStretch(1, 0)

    def read_serial_data(self):
        try:
            while self.serial_port.in_waiting > 0:  # When data is in the buffer
                data = self.serial_port.readline().decode('utf-8').strip()
                if not data.startswith("DATA"):
                    continue
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
        # Clear the label display area
        while self.label_layout.count():
            widget = self.label_layout.takeAt(0).widget()
            if widget:
                widget.deleteLater()
        # Highlight the label with the highest score
        max_label = max(labels_and_scores, key=labels_and_scores.get)
        max_score = labels_and_scores[max_label]
        for label, score in labels_and_scores.items():
            color = QColor(255, 0, 0) if label == max_label else QColor(0, 0, 0)
            label_widget = QLabel(f"{label}: {score:.2f}")
            label_widget.setStyleSheet(f"color: {color.name()}; font-size: 60px;")
            label_widget.setAlignment(Qt.AlignLeft)
            self.label_layout.addWidget(label_widget)

    def update_plot(self, labels_and_scores):
        for label, score in labels_and_scores.items():
            self.plot_canvas.add_data(label, score)
        self.plot_canvas.update_plot()


# Main Function
def main():
    app = QApplication(sys.argv)
    # Retrieve COM port name from command-line arguments
    if len(sys.argv) > 1:
        com_port = sys.argv[1]
    else:
        print('Usage: ', sys.argv[0], 'COMx')
        exit()

    # Serial Port Settings
    try:
        serial_port = serial.Serial(com_port, baudrate=115200, timeout=1)
        serial_port.flushInput()
        while serial_port.in_waiting > 0:
            data = serial_port.readline().decode('utf-8').strip()
    except Exception as e:
        print(f"Error opening serial port: {e}")
        sys.exit(1)

    # Initialization and Execution of the Main Window
    window = MainWindow(serial_port)
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()