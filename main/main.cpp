#include <iostream>
#include <windows.h>
#include <PluginAPI.h>
#include <memory>

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

  typedef yapi::YAPI* (*CreatePluginFunc)(void);

  SmartLoadLibrary lib1("DataSenderPlugin.dll");
  SmartLoadLibrary lib2("DataReceiverPlugin.dll");
  
  if (lib1.libHandle == nullptr) {
    std::cerr << "Failed to load filter1" << std::endl;
    return 0;
  }
  if (lib2.libHandle == nullptr) {
    std::cerr << "Failed to load filter2" << std::endl;
    return 0;
  }

  CreatePluginFunc createPlugin1 = (CreatePluginFunc)GetProcAddress(lib1.libHandle, "createPlugin");
  CreatePluginFunc createPlugin2 = (CreatePluginFunc)GetProcAddress(lib2.libHandle, "createPlugin");
  
  std::unique_ptr<yapi::YAPI> plugin1 = std::unique_ptr<yapi::YAPI>(createPlugin1());
  std::unique_ptr<yapi::YAPI> plugin2 = std::unique_ptr<yapi::YAPI>(createPlugin2());

  std::cout << "Loaded " << plugin1->GetPluginName() << std::endl;
  std::cout << "Loaded " << plugin2->GetPluginName() << std::endl;

  try {
    plugin1->Connect("Output", plugin2->GetInputPin("Input"));
  }
  catch (std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
    return 0;
  }

  plugin1->Start();
  plugin2->Start();

  system("pause");

  plugin1->Stop();
  plugin2->Stop();

  return 0;
}
