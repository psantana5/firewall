import logging
from logging.handlers import RotatingFileHandler
import sys
import re
import time
import os
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.cluster import KMeans
from sklearn.metrics import pairwise_distances_argmin_min

# Configure the logger
LOG_FILENAME = 'firewall.log'
LOG_FORMAT = '%(asctime)s - %(levelname)s - %(message)s'
LOG_MAX_SIZE = 1024 * 1024  # 1 MB
LOG_BACKUP_COUNT = 5

def setup_logger():
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)
    formatter = logging.Formatter(LOG_FORMAT)

    file_handler = RotatingFileHandler(LOG_FILENAME, maxBytes=LOG_MAX_SIZE, backupCount=LOG_BACKUP_COUNT)
    file_handler.setFormatter(formatter)
    logger.addHandler(file_handler)

    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.setFormatter(formatter)
    logger.addHandler(console_handler)

    return logger

# Log a message with the given severity level
def log_message(message, severity):
    if severity == 'INFO':
        logger.info(message)
    elif severity == 'WARNING':
        logger.warning(message)
    elif severity == 'ERROR':
        logger.error(message)
    elif severity == 'CRITICAL':
        logger.critical(message)

# Perform anomaly detection on the log file
def detect_anomalies():
    # Read log file
    with open(LOG_FILENAME, 'r') as file:
        logs = file.readlines()

    # Preprocess logs
    processed_logs = []
    for log in logs:
        # Remove timestamp and severity level from log message
        log = re.sub(r'^.*?- (.*?) - ', '', log)
        processed_logs.append(log)

    # Vectorize log messages
    vectorizer = TfidfVectorizer(stop_words='english')
    X = vectorizer.fit_transform(processed_logs)

    # Perform clustering
    kmeans = KMeans(n_clusters=2, random_state=0).fit(X)
    centers = kmeans.cluster_centers_

    # Find the nearest log to each cluster center
    closest_logs = pairwise_distances_argmin_min(centers, X)

    # Identify anomalies
    anomalies = []
    for index in closest_logs[0]:
        anomalies.append(logs[index])

    return anomalies

# Main function
if __name__ == '__main__':
    logger = setup_logger()

    # Log some example messages
    log_message("Starting firewall...", 'INFO')
    log_message("Firewall initialized.", 'INFO')
    log_message("Invalid request detected.", 'WARNING')
    log_message("Error occurred while processing request.", 'ERROR')
    log_message("Critical system failure. Shutting down...", 'CRITICAL')

    # Perform anomaly detection
    anomalies = detect_anomalies()

    if len(anomalies) > 0:
        log_message("Anomalies detected:", 'WARNING')
        for anomaly in anomalies:
            log_message(anomaly, 'WARNING')
    else:
        log_message("No anomalies detected.", 'INFO')
