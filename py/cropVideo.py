"""This program will read input file and try to locate in the videos we're given the minute around around a seizure.
The objective is to help in the process of narrowing down the precision of the available data."""

import argparse
import exceptions

import cv2
import pathlib

if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('-f', required=True, type=str)
    parser.add_argument('-o', required=True, type=str)
    parser.add_argument('-d', required=True, type=int)

    config = vars(parser.parse_args())

    filename = config['f']
    output_filename = config['o']
    skip = config['d']

    # if not pathlib.Path(filename).is_file():
    #     raise exceptions.RuntimeError("{} is not file".format(filename))
    #
    # if not pathlib.Path(output_filename).is_file():
    #     raise exceptions.RuntimeError("{} is not file".format(filename))

    print 'Loading video...'
    cam = cv2.VideoCapture(filename)
    fps = int(cam.get(cv2.CAP_PROP_FPS) + 0.5)
    frameCount = cam.get(cv2.CAP_PROP_FRAME_COUNT)

    print 'Skiping {} frames'.format(skip)
    cam.set(cv2.CAP_PROP_POS_FRAMES, skip)

    height, width = int(cam.get(cv2.CAP_PROP_FRAME_HEIGHT)), int(cam.get(cv2.CAP_PROP_FRAME_WIDTH))
    originalFPS = cam.get(cv2.CAP_PROP_FPS)
    videoWriter = cv2.VideoWriter(output_filename, cv2.VideoWriter_fourcc(*'XVID'), originalFPS, (width, height))

    count = frameCount - skip

    print 'writing video'
    while count > 0:
        ch = cv2.waitKey(1)
        ret, frame = cam.read()
        count -= 1
        videoWriter.write(frame)

    cam.release()
    videoWriter.release()

    print "DONE"

