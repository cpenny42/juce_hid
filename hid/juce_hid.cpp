/*
  ==============================================================================

    juce_hid.cpp
    Created: 7 Dec 2017 3:16:59pm
    Author:  Chris Penny

  ==============================================================================
*/

#define HID_ERROR -1
#ifndef DEFAULT_SIZE
    #define DEFAULT_SIZE 2048
#endif

using namespace juce;

Result hid::init()
{
    int res = hid_init();
    return res == HID_ERROR
        ? Result::fail(TRANS("could not initialize hidapi"))
        : Result::ok();
}

Result hid::exit()
{
    int res = hid_exit();
    return res == HID_ERROR
        ? Result::fail(TRANS("could not exit hidapi"))
        : Result::ok();
}

hid::DeviceInfo::DeviceInfo()
: vendorId(0)
, productId(0)
, releaseNumber(0)
, usagePage(0)
, usage(0)
, interfaceNumber (0) {};

hid::DeviceInfo::DeviceInfo (const hid_device_info& info)
: path               (info.path)
, vendorId           (info.vendor_id)
, productId          (info.product_id)
, serialNumber       (info.serial_number)
, releaseNumber      (info.release_number)
, manufacturerString (info.manufacturer_string)
, productString      (info.product_string)
, usagePage          (info.usage_page)
, usage              (info.usage)
, interfaceNumber    (info.interface_number) {}

hid::DeviceInfo::DeviceInfo (const DeviceInfo& other)
: path               (other.path)
, vendorId           (other.vendorId)
, productId          (other.productId)
, serialNumber       (other.serialNumber)
, releaseNumber      (other.releaseNumber)
, manufacturerString (other.manufacturerString)
, productString      (other.productString)
, usagePage          (other.usagePage)
, usage              (other.usage)
, interfaceNumber    (other.interfaceNumber) {}

hid::DeviceInfo::DeviceInfo (const MutableDeviceInfo& other)
: path               (other.getPath())
, vendorId           (other.getVendorId())
, productId          (other.getProductId())
, serialNumber       (other.getSerialNumber())
, releaseNumber      (other.getReleaseNumber())
, manufacturerString (other.getManufacturerString())
, productString      (other.getProductString())
, usagePage          (other.getUsagePage())
, usage              (other.getUsage())
, interfaceNumber    (other.getInterfaceNumber()) {}

bool hid::DeviceInfo::operator== (const DeviceInfo& other) const
{
    return
       this->path               == other.path
    && this->vendorId           == other.vendorId
    && this->productId          == other.productId
    && this->serialNumber       == other.serialNumber
    && this->releaseNumber      == other.releaseNumber
    && this->manufacturerString == other.manufacturerString
    && this->productString      == other.productString
    && this->usagePage          == other.usagePage
    && this->usage              == other.usage
    && this->interfaceNumber    == other.interfaceNumber;
}

bool hid::DeviceInfo::operator== (const MutableDeviceInfo& other) const
{
    return
       this->path               == other.path
    && this->vendorId           == other.vendorId
    && this->productId          == other.productId
    && this->serialNumber       == other.serialNumber
    && this->releaseNumber      == other.releaseNumber
    && this->manufacturerString == other.manufacturerString
    && this->productString      == other.productString
    && this->usagePage          == other.usagePage
    && this->usage              == other.usage
    && this->interfaceNumber    == other.interfaceNumber;
}

bool hid::DeviceInfo::operator== (const DeviceIO& other) const
{
    return *this == other.getInfo();
}

const String&        hid::DeviceInfo::getPath()               const { return path; }
const unsigned short hid::DeviceInfo::getVendorId()           const { return vendorId; };
const unsigned short hid::DeviceInfo::getProductId()          const { return productId; };
const String&        hid::DeviceInfo::getSerialNumber()       const { return serialNumber; };
const unsigned short hid::DeviceInfo::getReleaseNumber()      const { return releaseNumber; };
const String&        hid::DeviceInfo::getManufacturerString() const { return manufacturerString; };
const String&        hid::DeviceInfo::getProductString()      const { return productString; };
const unsigned short hid::DeviceInfo::getUsagePage()          const { return usagePage; };
const unsigned short hid::DeviceInfo::getUsage()              const { return usage; };
const int            hid::DeviceInfo::getInterfaceNumber()    const { return interfaceNumber; };
const String         hid::DeviceInfo::getName()               const {
    return manufacturerString + " " + productString;
}

const hid::DeviceIO hid::DeviceInfo::connect() const
{
    return hid::connect(*this);
}

void hid::DeviceInfo::disconnect() const
{
    hid::disconnect();
}




















hid::MutableDeviceInfo::MutableDeviceInfo() {}
hid::MutableDeviceInfo::MutableDeviceInfo (const hid_device_info& info)
{
    path                = info.path;
    vendorId            = info.vendor_id;
    productId           = info.product_id;
    serialNumber        = info.serial_number;
    releaseNumber       = info.release_number;
    manufacturerString  = info.manufacturer_string;
    productString       = info.product_string;
    usagePage           = info.usage_page;
    usage               = info.usage;
    interfaceNumber     = info.interface_number;
}

hid::MutableDeviceInfo::MutableDeviceInfo (const hid::DeviceInfo& other)
{
    path                = other.getPath();
    vendorId            = other.getVendorId();
    productId           = other.getProductId();
    serialNumber        = other.getSerialNumber();
    releaseNumber       = other.getReleaseNumber();
    manufacturerString  = other.getManufacturerString();
    productString       = other.getProductString();
    usagePage           = other.getUsagePage();
    usage               = other.getUsage();
    interfaceNumber     = other.getInterfaceNumber();
}

hid::MutableDeviceInfo::MutableDeviceInfo (const hid::MutableDeviceInfo& other)
{
    path                = other.getPath();
    vendorId            = other.getVendorId();
    productId           = other.getProductId();
    serialNumber        = other.getSerialNumber();
    releaseNumber       = other.getReleaseNumber();
    manufacturerString  = other.getManufacturerString();
    productString       = other.getProductString();
    usagePage           = other.getUsagePage();
    usage               = other.getUsage();
    interfaceNumber     = other.getInterfaceNumber();
}

bool hid::MutableDeviceInfo::operator== (const DeviceInfo& other) const
{
    return
       this->path               == other.path
    && this->vendorId           == other.vendorId
    && this->productId          == other.productId
    && this->serialNumber       == other.serialNumber
    && this->releaseNumber      == other.releaseNumber
    && this->manufacturerString == other.manufacturerString
    && this->productString      == other.productString
    && this->usagePage          == other.usagePage
    && this->usage              == other.usage
    && this->interfaceNumber    == other.interfaceNumber;
}

bool hid::MutableDeviceInfo::operator== (const MutableDeviceInfo& other) const
{
    return
       this->path               == other.path
    && this->vendorId           == other.vendorId
    && this->productId          == other.productId
    && this->serialNumber       == other.serialNumber
    && this->releaseNumber      == other.releaseNumber
    && this->manufacturerString == other.manufacturerString
    && this->productString      == other.productString
    && this->usagePage          == other.usagePage
    && this->usage              == other.usage
    && this->interfaceNumber    == other.interfaceNumber;
}

bool hid::MutableDeviceInfo::operator== (const DeviceIO& other) const
{
    return *this == other.getInfo();
}

const String&        hid::MutableDeviceInfo::getPath()               const { return path; }
const unsigned short hid::MutableDeviceInfo::getVendorId()           const { return vendorId; };
const unsigned short hid::MutableDeviceInfo::getProductId()          const { return productId; };
const String&        hid::MutableDeviceInfo::getSerialNumber()       const { return serialNumber; };
const unsigned short hid::MutableDeviceInfo::getReleaseNumber()      const { return releaseNumber; };
const String&        hid::MutableDeviceInfo::getManufacturerString() const { return manufacturerString; };
const String&        hid::MutableDeviceInfo::getProductString()      const { return productString; };
const unsigned short hid::MutableDeviceInfo::getUsagePage()          const { return usagePage; };
const unsigned short hid::MutableDeviceInfo::getUsage()              const { return usage; };
const int            hid::MutableDeviceInfo::getInterfaceNumber()    const { return interfaceNumber; };
const String         hid::MutableDeviceInfo::getName()               const {
    return manufacturerString + " " + productString;
}

hid::DeviceIO hid::MutableDeviceInfo::connect() const
{
    return hid::connect(*this);
}

void hid::MutableDeviceInfo::disconnect() const
{
    hid::disconnect();
}




































hid::DeviceIterator::DeviceIterator (unsigned short vid, unsigned short pid)
: current(hid_enumerate(vid, pid)) 
{
	DeleteThis = current;
}

hid::DeviceIterator::~DeviceIterator()
{
    hid_free_enumeration(DeleteThis);
}

bool hid::DeviceIterator::hasNext()
{
    return current != nullptr;
}

hid::DeviceInfo hid::DeviceIterator::getNext()
{
    // You must call hasNext() first to see if there is one available!
    // Program will crash if you try to getNext() when there are none.
    jassert(current != nullptr);
    
    hid_device_info* deviceToReturn = current;
    current = current->next;
    
    return *deviceToReturn;
}












hid::DeviceIO::DeviceIO (Device deviceToUse, const DeviceInfo& deviceInfo)
                      : device(deviceToUse), info(deviceInfo) {}

hid::DeviceIO::DeviceIO (const DeviceIO& other) : device(other.device), info(other.info) {}

bool hid::DeviceIO::operator==(const DeviceIO& other) const
{
    return
       this->device == other.device
    && DeviceInfo(this->info) == DeviceInfo(other.info);
}

bool hid::DeviceIO::operator==(const DeviceInfo& other) const
{
    return getInfo() == other;
}

bool hid::DeviceIO::operator==(const MutableDeviceInfo& other) const
{
    return getInfo() == other;
}

Result hid::DeviceIO::setNonblocking(bool shouldBeNonblocking)
{
    int r = hid_set_nonblocking(device, shouldBeNonblocking);
    return r == HID_ERROR
        ? Result::fail(TRANS(hid_error(device)))
        : Result::ok();
}

Result hid::DeviceIO::write(const unsigned char *data, size_t length, size_t* bytesWritten)
{
    int r = hid_write(device, data, length);
    if (bytesWritten != nullptr) {
        *bytesWritten = (size_t) r;
    }
    return r == 0
        ? Result::fail(TRANS("no bytes written"))
        : r == HID_ERROR
            ? Result::fail(TRANS(hid_error(device)))
            : Result::ok();
}

Result hid::DeviceIO::read(unsigned char *data, size_t length, size_t* bytesRead)
{
    int r = hid_read(device, data, length);
    
    if (bytesRead != nullptr) {
        *bytesRead = (size_t) r;
    }
    return r == 0
        ? Result::fail(TRANS("no bytes read"))
        : r == HID_ERROR
            ? Result::fail(TRANS(hid_error(device)))
            : Result::ok();
}

Result hid::DeviceIO::readTimeout(unsigned char *data, size_t length, int milliseconds, size_t* bytesRead)
{
    int r = hid_read_timeout (device, data, length, milliseconds);

    if (bytesRead != nullptr) {
        *bytesRead = (size_t) r;
    }
    return r == 0
        ? Result::fail(TRANS("no bytes read"))
        : r == HID_ERROR
            ? Result::fail(TRANS(hid_error(device)))
            : Result::ok();
}

Result hid::DeviceIO::sendFeatureReport(const unsigned char *data, size_t length, size_t* bytesWritten)
{
    int r = hid_send_feature_report(device, data, length);
    if (bytesWritten != nullptr) {
        *bytesWritten = (size_t) r;
    }
    return r == 0
        ? Result::fail(TRANS("no bytes written"))
        : r == HID_ERROR
            ? Result::fail(TRANS(hid_error(device)))
            : Result::ok();
}

Result hid::DeviceIO::getFeatureReport(unsigned char *data, size_t length, size_t* bytesRead)
{
    int r = hid_get_feature_report(device, data, length);

    if (bytesRead != nullptr) {
        *bytesRead = (size_t) r;
    }
    return r == 0 || r == 1
        ? Result::fail(TRANS("no bytes read"))
        : r == HID_ERROR
            ? Result::fail(TRANS(hid_error(device)))
            : Result::ok();
}

Result hid::DeviceIO::getManufacturerString(wchar_t* string, size_t maxLength)
{
    int r = hid_get_manufacturer_string(device, string, maxLength);
    return r == HID_ERROR
        ? Result::fail(TRANS(hid_error(device)))
        : Result::ok();
}

Result hid::DeviceIO::getProductString(wchar_t* string, size_t maxLength)
{
    int r = hid_get_product_string(device, string, maxLength);
    return r == HID_ERROR
        ? Result::fail(TRANS(hid_error(device)))
        : Result::ok();
}

Result hid::DeviceIO::getSerialNumberString(wchar_t* string, size_t maxLength)
{
    int r = hid_get_serial_number_string(device, string, maxLength);
    return r == HID_ERROR
        ? Result::fail(TRANS(hid_error(device)))
        : Result::ok();
}

Result hid::DeviceIO::getIndexedString(int index, wchar_t* string, size_t maxLength)
{
    int r = hid_get_indexed_string(device, index, string, maxLength);
    return r == HID_ERROR
        ? Result::fail(TRANS("hid_get_indexed_string not implemented on macOS"))
        : Result::ok();
}

void hid::DeviceIO::disconnect()
{
    if (device == nullptr || ! hid::isConnected()) {
        DBG("    Warning: disconnecting device when none are connected.");
    }
    hid_close(device);
    device = nullptr;
}

Result hid::DeviceIO::connect()
{
    if (device != nullptr || hid::isConnected()) {
        return Result::fail(TRANS("Already connected to device"));
    }
    
    *this = info.connect();
    
    if (device == nullptr) {
        return Result::fail(TRANS("failed to connect to device"));
    }
    
    return Result::ok();
}

const hid::DeviceInfo hid::DeviceIO::getInfo() const
{
    return info;
}


















hid::DeviceScanner::DeviceScanner() : DeviceScanner (nullptr) {}
hid::DeviceScanner::DeviceScanner(ChangeListener* listener, int intervalInMilliseconds)
{
    if (listener != nullptr) {
        addChangeListener(listener);
    }
    startTimer(intervalInMilliseconds);
}

hid::DeviceScanner::~DeviceScanner()
{
    removeAllChangeListeners();
    stopTimer();
}

void hid::DeviceScanner::timerCallback()
{
    scanNow();
}

const Array<hid::DeviceInfo>& hid::DeviceScanner::getCurrentDevices() const
{
    return devices;
}

void hid::DeviceScanner::scanNow()
{
    Array<DeviceInfo> newDevices = hid::getAllDevicesAvailable();
    
    // Device removed or connected
    if (newDevices.size() != devices.size()) {
        devices = newDevices;
        sendChangeMessage();
    }
}


























bool hid::isDeviceAvailable (unsigned short vid, unsigned short pid)
{
    hid::DeviceIterator iterator (vid, pid);
    return iterator.hasNext();
}

hid::DeviceInfo hid::getDeviceInfo(unsigned short vid, unsigned short pid)
{
    hid::DeviceIterator iterator (vid, pid);
    
    // Can't get the next device when there are none! Check if it's availiable with
    // isDeviceAvailable (unsigned short vid, unsigned short pid).
    jassert(iterator.hasNext());
    return iterator.getNext();
}

Array<hid::DeviceInfo> hid::getAllDevicesAvailable()
{
    Array<DeviceInfo> allDevices;
    hid::DeviceIterator iterator;
    while (iterator.hasNext()) {
        allDevices.add(iterator.getNext());
    }
    return allDevices;
}

void hid::printAllDevices()
{
    hid::DeviceIterator iterator;
    
    while (iterator.hasNext())
    {
        DeviceInfo currentDevice (iterator.getNext());
        
        String s;
        String usage_str;
        s += "0x" + String::toHexString (currentDevice.getVendorId()).paddedLeft('0', 4) + ":";
        s += "0x" + String::toHexString (currentDevice.getProductId()).paddedLeft('0', 4);
        s += String(" ") + currentDevice.getManufacturerString();
        s += String(" ") + currentDevice.getProductString();
        
        usage_str += "0x" + String::toHexString (currentDevice.getUsagePage()).paddedLeft('0', 4);
        usage_str += ":0x" + String::toHexString (currentDevice.getUsage()).paddedLeft('0', 4);
        s += " " + usage_str;
        
        std::cout << s << "\n";
        std::cout << currentDevice.getPath() << "\n\n";
    }
}

hid::DeviceIO hid::getConnectedDevice()
{
    // Don't call this function if no device is connected!!!!!!!
    jassert(isConnected());
    
    return changeConnection(false, DeviceInfo(hid_device_info()), true);
}

const hid::DeviceInfo hid::getConnectedDeviceInfo()
{
    // Don't call this function if no device is connected!!!!!!!
    jassert(isConnected());
    
    return getConnectedDevice().getInfo();
}

bool hid::isConnected()
{
    return connectionStatus(false);
}

hid::DeviceIO hid::connect (const DeviceInfo& device)
{
    return changeConnection(true, device);
}

void hid::disconnect()
{
    changeConnection(false);
}

const unsigned int hid::reportID()
{
    static unsigned int idCounter = 0;
    return idCounter++;
}

// Why use a class when you could use a function
// Don't worry it's a rhetorical question — this approach worked for my
// specific use case, but this could easily be replaced with something
// a little more clear.
//
// These functions maintain an internal static device representation and 
// are the single point of entry for all connection/disconnection related things.
// Note that this only supports one connection at a time.
bool hid::connectionStatus (bool shouldSet, bool shouldBeConnected)
{
    static bool isConnected = false;

    if (shouldSet) {
        isConnected = shouldBeConnected;
    }
    
    return isConnected;
}

hid::DeviceIO hid::changeConnection(bool shouldConnect, const DeviceInfo& deviceInfo, bool get)
{
    static MutableDeviceInfo connectedDeviceInfo;
    static Device connectedDevice = nullptr;
    
    if (get) {
        return DeviceIO(connectedDevice, connectedDeviceInfo);
    }
    connectionStatus(true, false);
    if (shouldConnect) {
        if ((connectedDevice = hid_open_path(deviceInfo.getPath().toRawUTF8())) != nullptr) {
            // Connection Success
            connectedDeviceInfo = deviceInfo;
            DBG("    HID Device Connected: " << deviceInfo.getName());
            connectionStatus(true, true);
        }
        else {
            DBG("    HID Device Failed To Connect: " << deviceInfo.getName());
        }
    }
    else if (connectedDevice != nullptr) {
        hid_close(connectedDevice);
        connectedDevice = nullptr;
        DBG("    HID Device Disconnected: " << connectedDeviceInfo.getName());
    }
    else {
        DBG("    Could not disconnect HID Device - none connected.");
    }

    return DeviceIO(connectedDevice, connectedDeviceInfo);
}
