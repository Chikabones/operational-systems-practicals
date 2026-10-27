import time
import sys

log_file = '/var/log/time_writer.log'
print(f'Starting Time Writer Service. Logging to {log_file}', flush=True)

while True:
    current_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
    try:
        with open(log_file, 'a') as f:
            f.write(f'Timestamp: {current_time}\n')
    except Exception as e:
        print(f'Error writing log: {e}', file=sys.stderr)
    time.sleep(10)