#!/bin/bash

# 移動
cd /home/ubuntu/catkin_ws/src/

# 依存関係のインストール
rosdep install -r -y -i --from-paths .
python3 -m pip install -r ultralytics_ros/requirements.txt

# ビルド
cd /home/ubuntu/catkin_ws/
source /opt/ros/noetic/setup.bash
catkin_make

# すべてのプロセスが完了したら、コンテナが終了しないようにbashを実行
exec bash
