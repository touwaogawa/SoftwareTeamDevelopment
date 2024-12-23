#!/bin/bash

# LD_LIBRARY_PATHに../libを追加
export LD_LIBRARY_PATH=../lib:$LD_LIBRARY_PATH

# 環境変数が正しく設定されたか確認するために表示（オプション）
echo "LD_LIBRARY_PATH is set to: $LD_LIBRARY_PATH"