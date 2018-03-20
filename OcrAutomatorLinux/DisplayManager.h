#pragma once
#include "Master/MasterProcessingWorker.h"
#include "Slave/SlaveProcessingWorker.h"

void MasterDisplayUI();
void SlaveDisplayUI();

extern Docapost::IA::Tesseract::MasterProcessingWorker* workerM;
extern Docapost::IA::Tesseract::SlaveProcessingWorker* workerS;

#if DISPLAY
#include "Master/Display.h"
#include "Slave/SlaveDisplay.h"

void resizeHandler(int sig);

Display* display;
SlaveDisplay* sdisplay;

#endif