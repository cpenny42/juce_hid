/*
  ==============================================================================
 
    juce_hid.h
    Created: 6 Dec 2017 8:18:00pm
    Author:  Chris Penny
 
  ==============================================================================
*/

#pragma once

// This is NOT thread-safe! It does not support multiple connections to different
// HID devices! This library is only useful when you are connecting to a single 
// HID device at a time.
struct hid {
    
    /** @brief Initialize the HIDAPI library.
     
        This function initializes the HIDAPI library. Calling it is not
        strictly necessary, as it will be called automatically by other
        functions if it is needed.  This function should be called at the
        beginning of execution however, if there is a chance of HIDAPI
        handles being opened by different threads simultaneously.
     
        @ingroup API
     
        @returns
        This function returns 0 on success and -1 on error.
     */
    static juce::Result init();
    
    /** @brief Finalize the HIDAPI library.
     
        This function frees all of the static data associated with
        HIDAPI. It should be called at the end of execution to avoid
        memory leaks.
     
        @ingroup API
     
        @returns
        This function returns 0 on success and -1 on error.
     */
    static juce::Result exit();
    
    typedef hid_device* Device;
    class DeviceInfo;
    class MutableDeviceInfo;
    class DeviceIO;
    
    /** Holds all the information associated with a device.
     */
    //=========================================================================
    //=========================================================================
    class DeviceInfo
    {
    public:
        
        DeviceInfo();
        DeviceInfo (const hid_device_info& info);
        DeviceInfo (const DeviceInfo& other);
        DeviceInfo (const MutableDeviceInfo& other);
        bool operator== (const DeviceInfo& other) const;
        bool operator== (const MutableDeviceInfo& other) const;
        bool operator== (const DeviceIO& other) const;

        const juce::String&  getPath()               const;
        const unsigned short getVendorId()           const;
        const unsigned short getProductId()          const;
        const juce::String&  getSerialNumber()       const;
        const unsigned short getReleaseNumber()      const;
        const juce::String&  getManufacturerString() const;
        const juce::String&  getProductString()      const;
        const unsigned short getUsagePage()          const;
        const unsigned short getUsage()              const;
        const int            getInterfaceNumber()    const;
        const juce::String  getName()               const;
        
        const DeviceIO connect() const;
        void disconnect() const;
        
    private:
        
        const juce::String   path;
        const unsigned short vendorId;
        const unsigned short productId;
        const juce::String   serialNumber;
        const unsigned short releaseNumber;
        const juce::String   manufacturerString;
        const juce::String   productString;
        const unsigned short usagePage;
        const unsigned short usage;
        const int            interfaceNumber;
        
        friend class MutableDeviceInfo;
        JUCE_LEAK_DETECTOR(DeviceInfo)
    };
    
    
    /** Exact same as DeviceInfo, but is mutable.
     *  Example:
     *
     *      DeviceInfo info1;
     *      DeviceInfo info2;
     *      info1 = info2; // ERROR - not allowed
     *
     *      MutableDeviceInfo mutableInfo1;
     *      MutableDeviceInfo mutableInfo2;
     *      mutableInfo1 = mutableInfo2;   // Allowed, 1 is now a copy of 2
     *
     *  I really like immutable data structures, but I like it even better
     *  when it is explicit when a data structure is mutable or immutable.
     *  I know this seems redundant and unnecessary. Sue me. 
     *  You really shouldn't ever use this class — it's used internally.
     *  Immutable == better, except in cases where you're forced to do otherwise.
     */
    //=========================================================================
    //=========================================================================
    class MutableDeviceInfo
    {
    public:
        
        MutableDeviceInfo ();
        MutableDeviceInfo (const hid_device_info& info);
        MutableDeviceInfo (const DeviceInfo& other);
        MutableDeviceInfo (const MutableDeviceInfo& other);
        bool operator== (const DeviceInfo& other) const;
        bool operator== (const MutableDeviceInfo& other) const;
        bool operator== (const DeviceIO& other) const;
        
        const juce::String&  getPath()               const;
        const unsigned short getVendorId()           const;
        const unsigned short getProductId()          const;
        const juce::String&  getSerialNumber()       const;
        const unsigned short getReleaseNumber()      const;
        const juce::String&  getManufacturerString() const;
        const juce::String&  getProductString()      const;
        const unsigned short getUsagePage()          const;
        const unsigned short getUsage()              const;
        const int            getInterfaceNumber()    const;
        const juce::String   getName()               const;
        
        DeviceIO connect() const;
        void disconnect() const;
        
    private:
        
        juce::String   path;
        unsigned short vendorId;
        unsigned short productId;
        juce::String   serialNumber;
        unsigned short releaseNumber;
        juce::String   manufacturerString;
        juce::String   productString;
        unsigned short usagePage;
        unsigned short usage;
        int            interfaceNumber;
        
        friend class DeviceInfo;
        JUCE_LEAK_DETECTOR(MutableDeviceInfo)
    };
    
    
    /** Handles all reading/writing
     */
    //=========================================================================
    //=========================================================================
    class DeviceIO
    {
    public:

        /** Create from Device (opaque API pointer) & deviceInfo.
         *
         *  You'd usually never create one of these on your own.
         *  Get one from calling DeviceInfo::connect() or hid::getConnectedDevice() 
         *
         *  Note that Device is an alias for hid_device (from hidapi.h)
         */
        DeviceIO (Device deviceToUse, const DeviceInfo& deviceInfo);
        
        /** Copy Constructor
         */
        DeviceIO (const DeviceIO& other);
        
        /** @brief Set the device handle to be non-blocking.
         
            In non-blocking mode calls to hid_read() will return
            immediately with a value of 0 if there is no data to be
            read. In blocking mode, hid_read() will wait (block) until
            there is data to read before returning.
        
            Nonblocking can be turned on and off at any time.
        
            @ingroup API
            @param device A device handle returned from hid_open().
            @param nonblock enable or not the nonblocking reads
            - 1 to enable nonblocking
            - 0 to disable nonblocking.
        
         @returns
         This function returns 0 on success and -1 on error.
         */
        juce::Result setNonblocking (bool shouldBeNonblocking);
        
        /** @brief Write an Output report to a HID device.
         
         write() will send the data on the first OUT endpoint, if
         one exists. If it does not, it will send the data through
         the Control Endpoint (Endpoint 0).
         
         @param data The data to send
         @param length The length in bytes of the data to send.
         @param bytesWritten Optional int reference that will store 
         the actual number of bytes written or -1 on error.
         
         @returns
         The Result of the write.
         */
        juce::Result write (const unsigned char *data, size_t length, size_t* bytesWritten = nullptr);
        
        /** @brief Read an Input report from a HID device.
         
         Input reports are returned
         to the host through the INTERRUPT IN endpoint
         
         @param data A buffer to put the read data into.
         @param length The number of bytes to read.
         @param bytesRead Optional int reference that will store
         the actual number of bytes read or -1 on error.
         
         @returns
         The Result of the read.
         */
        juce::Result read (unsigned char *data, size_t length, size_t* bytesRead = nullptr);
        
        /** @brief Read an Input report from a HID device with timeout.
         
         Input reports are returned
         to the host through the INTERRUPT IN endpoint.
         
         @param data A buffer to put the read data into.
         @param length The number of bytes to read.
         @param milliseconds timeout in milliseconds or -1 for blocking wait.
         @param bytesRead Optional int reference that will store
         the actual number of bytes read or -1 on error.
         
         @returns
         The result of the read. If no packet was available to be read within
         the timeout period, this function returns Result::fail.
         */
        juce::Result readTimeout (unsigned char *data, size_t length, int milliseconds, size_t* bytesRead = nullptr);
        
        /** @brief Send a Feature report to the device.
         
         Feature reports are sent over the Control endpoint as a
         Set_Report transfer.
         
         @param data The data to send
         @param length The length in bytes of the data to send
         @param bytesWritten Optional int reference that will store
         the actual number of bytes read or -1 on error.

         @returns
         The result of the write.
         */
        juce::Result sendFeatureReport (const unsigned char *data, size_t length, size_t* bytesWritten = nullptr);
        
        /** @brief Get a feature report from a HID device.

         @param data A buffer to put the read data into
         @param length The number of bytes to read. The buffer can be longer
         than the actual report.
         @param bytesRead Optional int reference that will store
         the actual number of bytes read plus
         one for the report ID, or -1 on error.

         @returns
         The result of the write.
         */
        juce::Result getFeatureReport (unsigned char *data, size_t length, size_t* bytesRead = nullptr);
        
        /** @brief Get The Manufacturer String from a HID device.
         
         @param string A wide string buffer to put the data into.
         @param maxlen The length of the buffer in multiples of wchar_t.
         
         @returns
         This function returns Result::ok on success and Result::fail on error.
         */
        juce::Result getManufacturerString (wchar_t* string, size_t maxLength);
        
        /** @brief Get The Product String from a HID device.
         
         @param string A wide string buffer to put the data into.
         @param maxlen The length of the buffer in multiples of wchar_t.
         
         @returns
         This function returns Result::ok on success and Result::fail on error.
         */
        juce::Result getProductString (wchar_t* string, size_t maxLength);
        
        /** @brief Get The Serial Number String from a HID device.
         
         @param string A wide string buffer to put the data into.
         @param maxlen The length of the buffer in multiples of wchar_t.
         
         @returns
         This function returns Result::ok on success and Result::fail on error.
         */
        juce::Result getSerialNumberString (wchar_t* string, size_t maxLength);
        
        /** @brief Get a string from a HID device, based on its string index.
         
         @param string_index The index of the string to get.
         @param string A wide string buffer to put the data into.
         @param maxlen The length of the buffer in multiples of wchar_t.
         
         @returns
         This function returns Result::ok on success and Result::fail on error.
         */
        juce::Result getIndexedString (int index, wchar_t* string, size_t maxLength);
        
        /** Connect to this device. Returns Result::fail if already connected
         */
        juce::Result connect();
        
        /** Disconnect from the device. Returns Result::fail if not connected.
         */
        void disconnect();
        
        /** Returns the DeviceInfo associated with this DeviceIO.
         *
         *  DeviceInfo & DeviceIO always both refer to the same unique device
         */
        const DeviceInfo getInfo() const;
        
        bool operator== (const DeviceIO& other) const;
        bool operator== (const DeviceInfo& other) const;
        bool operator== (const MutableDeviceInfo& other) const;
        
    private:

        Device device;
        MutableDeviceInfo info;
        JUCE_LEAK_DETECTOR(DeviceIO)
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    /**  Iterates through all the availiable devices, optionally with a given
     *  VendorID and ProductID.
     *
     *  Call DeviceIterator::hasNext() to see if there are any available,
     *  and DeviceIterator::getNext() to get them. Do not call getNext() when
     *  there are no devices available — this will crash the program.
     */
    //=========================================================================
    //=========================================================================
    class DeviceIterator
    {
    public:
        
        /** Create an iterator from a VendorID & ProductID */
        DeviceIterator (unsigned short vendorID  = 0,
                        unsigned short productID = 0);
        
        /**
         */
        ~DeviceIterator();
        
        /** Returns true if there is another device to get via getNext()
         */
        bool hasNext();
        
        /**  Returns the next DeviceInfo available.
         *  You MUST call hasNext() first to see if there are any available.
         *  Program will crash if you call getNext() when there are no more devices available.
         */
        DeviceInfo getNext();
        
    private:
        
        JUCE_LEAK_DETECTOR(DeviceIterator)
        hid_device_info* current;
        hid_device_info* DeleteThis;
    };
    
    
    
    /** Frequently scans for HID Devices and sends a change message when one is added/removed.
     *  Call DeviceScanner::addChangeListener (ChangeListener* listener) to be notified when devices
     *  are connected or disconnected.
     */
    //=========================================================================
    //=========================================================================
    class DeviceScanner :   public juce::ChangeBroadcaster, private juce::Timer
    {
    public:
        
        DeviceScanner();
        DeviceScanner (juce::ChangeListener* listener, int intervalInMilliseconds = 500);
        ~DeviceScanner();
        
        /** Returns all devices that are available from the most recent scan.
         */
        const juce::Array<DeviceInfo>& getCurrentDevices() const;
        
        /** Scans for devices immediately
         */
        void scanNow();
        
    private:
        
        void timerCallback();
        juce::Array<DeviceInfo> devices;
        
        JUCE_LEAK_DETECTOR(DeviceScanner)
    };
    
    
    
    
    
    
    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    
    /**  Returns true if a device with the vid & pid exists.
     */
    static bool isDeviceAvailable (unsigned short vendorID, unsigned short productID);
    
    /**  Gets the device information for a given VendorID and ProductID.
     *  If multiple devices with the same vid & pid are available, this returns
     *  the first one.
     *
     *  Do not call this unless isDeviceAvailable  returns true for your vid & pid
     */
    static DeviceInfo getDeviceInfo(unsigned short vendorID, unsigned short productID);
    
    /**  Returns a list of all the devices available
     */
    static juce::Array<DeviceInfo> getAllDevicesAvailable();
    
    /**  Prints info about all the available devices.
     */
    static void printAllDevices();
    
    /** returns true if there currently is an active connection
     */
    static bool isConnected();
    
    /** Returns the DeviceIO that is currently connected.
     *  If there is no connection, the DeviceIO returned is invalid and shouldn't
     *  be used.
     *
     *  Check isConnected() first before trying getConnectedDevice()!
     */
    static DeviceIO getConnectedDevice();
    
    /** Returns the DeviceInfo for the connected device.
     *  If no device is connected, the DeviceInfo is invalid and shouldn't be used.
     *
     *  Check isConnected() first before trying getConnectedDeviceInfo()
     */
    static const DeviceInfo getConnectedDeviceInfo();
    
    /** Connects to a device (only one connection allowed at a time, for now)
     */
    static DeviceIO connect (const DeviceInfo& device);
    
    /** Disconnects from the currently connected device (does nothing if not connected)
     */
    static void disconnect();
    
    /** Always returns a unique report ID.
     */
    static const unsigned int reportID();
    
private:
    
    /** INTERNAL */
    static bool connectionStatus (bool shouldSet, bool shouldBeConnected = true);
    static DeviceIO changeConnection(bool shouldConnect,
                                     const DeviceInfo& device = DeviceInfo(hid_device_info()),
                                     bool get = false);
    
}; 
