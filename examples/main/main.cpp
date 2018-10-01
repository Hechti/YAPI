#include <iostream>
#include <windows.h>
#include <Yapi.h>
#include <memory>
#include <chrono>

class SmartLoadLibrary
{
public:
  SmartLoadLibrary(const char* address)
  {
    libHandle = LoadLibrary(address);
  }

  ~SmartLoadLibrary()
  {
    if (libHandle != nullptr) {
      FreeLibrary(libHandle);
    }
  }

  HINSTANCE libHandle;
};

int main()
{
  std::cout << "======================================" << std::endl;
  std::cout << "================YAPI 1================" << std::endl;
  std::cout << "======================================" << std::endl << std::endl;

  //typedef yapi::YAPI* (*CreatePluginFunc)(void);
  using CreatePluginFunc = yapi::YAPI* (*)();

  SmartLoadLibrary lib1("DataSenderPlugin.dll");
  SmartLoadLibrary lib2("DataReceiverPlugin.dll");
  SmartLoadLibrary lib3("CyclicSenderPlugin.dll");
  
  if (lib1.libHandle == nullptr) {
    std::cerr << "Failed to load filter1" << std::endl;
    return 0;
  }
  if (lib2.libHandle == nullptr) {
    std::cerr << "Failed to load filter2" << std::endl;
    return 0;
  }
  if (lib3.libHandle == nullptr) {
      std::cerr << "Failed to load filter3" << std::endl;
      return 0;
  }
  CreatePluginFunc createPlugin1 = (CreatePluginFunc)GetProcAddress(lib1.libHandle, "createPlugin");
  CreatePluginFunc createPlugin2 = (CreatePluginFunc)GetProcAddress(lib2.libHandle, "createPlugin");
  CreatePluginFunc createPlugin3 = (CreatePluginFunc)GetProcAddress(lib3.libHandle, "createPlugin");
  
  std::unique_ptr<yapi::YAPI> plugin1 = std::unique_ptr<yapi::YAPI>(createPlugin1());
  std::unique_ptr<yapi::YAPI> plugin2 = std::unique_ptr<yapi::YAPI>(createPlugin2());
  std::unique_ptr<yapi::YAPI> plugin3 = std::unique_ptr<yapi::YAPI>(createPlugin3());

  std::cout << "Loaded " << plugin1->GetPluginName() << std::endl;
  std::cout << "Loaded " << plugin2->GetPluginName() << std::endl;
  std::cout << "Loaded " << plugin3->GetPluginName() << std::endl;

  try {
    plugin1->Connect("Output", plugin2->GetInputPin("Input"));
    plugin3->Connect("Output", plugin2->GetInputPin("Input"));
  }
  catch (std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
    return 0;
  }

  const std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

  plugin1->SetStartTime(startTime);
  plugin2->SetStartTime(startTime);
  plugin3->SetStartTime(startTime);

  plugin1->Start();
  plugin2->Start();
  plugin3->Start();

  system("pause");

  plugin1->Stop();
  plugin2->Stop();
  plugin3->Stop();

  return 0;
}
