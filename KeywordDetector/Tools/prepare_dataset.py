import os
from pathlib import Path
import librosa
import tqdm
import random
import numpy as np
import soundfile

NUMBER_OF_SAMPLES_PER_FILE = 1000  # Number of samples per file, change if you want another length
FS = 16000  # Sample rate, change if you data was recorded with another sample rate
data_path = Path("path/to/raw/speechcommands/dataset")  # Path to the raw dataset (GoogleSpeechCommands)
target_path = Path("path/to/imagimob_project/Data")  # Path to the Imagimob project data folder

folders = [x[1] for x in os.walk(data_path) if x[1]][0]

recordings = []
sample_length = []
labels = []
label_times = []

for folder in tqdm.tqdm(folders):
    if "background" in folder: 
        # ignore the "background" folder which contains noise samples that can be layed over other samples
        continue
    src = data_path / folder
    files = [x[2] for x in os.walk(src) if x[2]][0]

    for i, file in enumerate(files):
        data, _ = librosa.load(path=src / file, sr=FS, mono=True)
        data = np.pad(data, (0, int(0.1 * FS)))
        recordings.append(data)

        avg = []
        snippet_length = 0.01
        snippet_points = int(snippet_length * FS)
        for s in range(0, len(data), snippet_points):
            avg.append(np.abs(data[s:s + snippet_points]).mean())
        threshold = np.median(np.abs(data)) + 0.5 * np.std(np.abs(data))
        label_time = np.where(avg > threshold)[0] * snippet_length

        labels.append(folder)
        label_times.append(label_time)
        sample_length.append(len(data) / FS)

temp = list(zip(recordings, sample_length, labels, label_times))
random.shuffle(temp)
recordings, sample_length, labels, label_times = zip(*temp)


# new_files = []
for i in range(round(len(recordings) / NUMBER_OF_SAMPLES_PER_FILE)):
    start = i * NUMBER_OF_SAMPLES_PER_FILE
    stop = (i + 1) * NUMBER_OF_SAMPLES_PER_FILE
    if stop > len(recordings):
        stop = -1

    sample = np.concatenate(recordings[start:stop])
    lbls = labels[start:stop]
    lengths = sample_length[start:stop]
    timings = label_times[start:stop]

    dst = target_path / f"track_{i:03d}"
    os.makedirs(dst, exist_ok=True)
    time_passed = 0

    with soundfile.SoundFile(dst / 'data.wav', 'w', samplerate=FS, channels=1, subtype='PCM_16', format='WAV') as f:
        f.write(sample)
    with open(dst / "label.label", "w", encoding="utf-8") as label_file:
        label_file.write("Time(seconds), Length(seconds), Label(string), Confidence(double), Comment(string) \n")
        for lbl, length, timing in zip(lbls, lengths, timings):
            if len(timing) > 1:
                label_start = time_passed + timing[0]
                label_length = timing[-1]-timing[0]
                label_file.write(f"{label_start},{label_length},{lbl},{1.0},\n")
            time_passed += length
