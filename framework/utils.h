#ifndef FRAMEWORK_UTILS_H
#define FRAMEWORK_UTILS_H

#include <vector>
#include <string>

unsigned int loadTexture(const char* path);

unsigned int loadCubemap(std::vector<std::string> faces);

int saveScreenshot(const char* filename);

const char* createScreenshotBasename();

#endif  // FRAMEWORK_UTILS_H
