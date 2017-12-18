using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace TaskManager
{
    public class TaskManagerProcess : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private string _processName;
        public string ProcessName
        {
            get { return _processName; }
            set
            {
                _processName = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("ProcessName"));
            }
        }
        private int _PID;
        public int PID
        {
            get { return _PID; }
            set
            {
                _PID = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("PID"));
            }
        }
        private String _memory;
        public String Memory
        {
            get { return _memory; }
            set
            {
                _memory = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Memory"));
            }
        }

        private String _state;
        public String State
        {
            get { return _state; }
            set
            {
                _state = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("State"));
            }
        }

        private String _User;
        public String User
        {
            get { return _User; }
            set
            {
                _User = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("User"));
            }
        }

        private int _CPU;
        public int CPU
        {
            get { return _CPU; }
            set
            {
                _CPU = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("CPU"));
            }
        }

        private string _description;
        public string Description
        {
            get { return _description; }
            set
            {
                _description = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Description"));
            }
        }

        private int _pageFaultCount;
        public int PageFaultCount
        {
            get { return _pageFaultCount; }
            set
            {
                _pageFaultCount = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("PageFaultCount"));
            }
        }

        private long _peakWorkingSetSize;
        public long PeakWorkingSetSize
        {
            get { return _peakWorkingSetSize; }
            set
            {
                _peakWorkingSetSize = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("PeakWorkingSetSize"));
            }
        }

        private int _quotaPeakPagedPoolUsage;
        public int QuotaPeakPagedPoolUsage
        {
            get { return _quotaPeakPagedPoolUsage; }
            set
            {
                _quotaPeakPagedPoolUsage = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("QuotaPeakPagedPoolUsage"));
            }
        }

        private int _quotaPagedPoolUsage;
        public int QuotaPagedPoolUsage
        {
            get { return _quotaPagedPoolUsage; }
            set
            {
                _quotaPagedPoolUsage = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("QuotaPagedPoolUsage"));
            }
        }

        private int _quotaPeakNonPagedPoolUsage;
        public int QuotaPeakNonPagedPoolUsage
        {
            get { return _quotaPeakNonPagedPoolUsage; }
            set
            {
                _quotaPeakNonPagedPoolUsage = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("QuotaPeakNonPagedPoolUsage"));
            }
        }

        private int _quotaNonPagedPoolUsage;
        public int QuotaNonPagedPoolUsage
        {
            get { return _quotaNonPagedPoolUsage; }
            set
            {
                _quotaNonPagedPoolUsage = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("QuotaNonPagedPoolUsage"));
            }
        }

        private long _peakPagefileUsage;
        public long PeakPagefileUsage
        {
            get { return _peakPagefileUsage; }
            set
            {
                _peakPagefileUsage = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("PeakPagefileUsage"));
            }
        }

        private long _pagefileUsage;
        public long PagefileUsage
        {
            get { return _pagefileUsage; }
            set
            {
                _pagefileUsage = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("PagefileUsage"));
            }
        }

        public static List<TaskManagerProcess> Update()
        {
            List<TaskManagerProcess> pList = new List<TaskManagerProcess>();
            Process[] localAll = Process.GetProcesses();
            Stopwatch watch = Stopwatch.StartNew();
            long cpuSum = 0;
            foreach (Process p in localAll)
            {
                PerformanceCounter pf1 = new PerformanceCounter("Process", "% Processor time", p.ProcessName);
                cpuSum += pf1.RawValue;
            }

            foreach (Process p in localAll)
            {
                string path = GetExecutablePath(p.Id);
                string description;
                string user;
                int cpu;
                try
                {
                    FileVersionInfo pFileVersionInfo = FileVersionInfo.GetVersionInfo(path);
                    description = pFileVersionInfo.FileDescription;

                    FileInfo fi = new FileInfo(path);
                    System.Security.AccessControl.FileSecurity fileSecurity = fi.GetAccessControl();
                    var userRef = fileSecurity.GetOwner(typeof(NTAccount));
                    user = userRef.Value;

                    PerformanceCounter pf1 = new PerformanceCounter("Process", "% Processor time", p.ProcessName);
                    cpu = (int)(pf1.RawValue * 100 / cpuSum);
                }
                catch(Exception)
                {
                    description = "未知";
                    user = "未知";
                    cpu = 0;
                }

                pList.Add(new TaskManagerProcess
                {
                    ProcessName = p.ProcessName,
                    PID = p.Id,
                    Memory = (p.WorkingSet64 / 1024).ToString()+"k",
                    State = p.Responding ? @"正在运行": @"已暂停",
                    CPU = cpu,
                    User = user,
                    Description = description,
                    PeakWorkingSetSize = p.PeakWorkingSet64,
                    PeakPagefileUsage = p.PeakPagedMemorySize64,
                    PagefileUsage = p.PagedMemorySize64
                });
                watch.Stop();
            }

            return pList;
        }

        // windows api
        [DllImport("kernel32.dll")]
        private static extern bool QueryFullProcessImageName(IntPtr hprocess, int dwFlags,
               StringBuilder lpExeName, out int size);
        [DllImport("kernel32.dll")]
        private static extern IntPtr OpenProcess(ProcessAccessFlags dwDesiredAccess,
                       bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool CloseHandle(IntPtr hHandle);

        [Flags]
        public enum ProcessAccessFlags : uint
        {
            All = 0x001F0FFF,
            Terminate = 0x00000001,
            CreateThread = 0x00000002,
            VirtualMemoryOperation = 0x00000008,
            VirtualMemoryRead = 0x00000010,
            VirtualMemoryWrite = 0x00000020,
            DuplicateHandle = 0x00000040,
            CreateProcess = 0x000000080,
            SetQuota = 0x00000100,
            SetInformation = 0x00000200,
            QueryInformation = 0x00000400,
            QueryLimitedInformation = 0x00001000,
            Synchronize = 0x00100000
        }

        private static string GetExecutablePath(int processId)
        {
            StringBuilder buffer = new StringBuilder(1024);
            IntPtr hprocess = OpenProcess(ProcessAccessFlags.QueryLimitedInformation, false, processId);
            if (hprocess != IntPtr.Zero)
            {
                try
                {
                    int size = buffer.Capacity;
                    if (QueryFullProcessImageName(hprocess, 0, buffer, out size))
                    {
                        return buffer.ToString();
                    }
                }
                finally
                {
                    CloseHandle(hprocess);
                }
            }
            return string.Empty;
        }
    }

}
