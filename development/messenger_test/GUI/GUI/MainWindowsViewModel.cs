using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows.Input;
using System.Runtime.InteropServices;
using System.Threading;

namespace GUI
{
    public class MainWindowsViewModel : INotifyPropertyChanged
    {

        //field
        private ICommand _myCommand;
        private ICommand _Login_command;
        private ICommand _show_users;

        private bool flag = false;
        private int _selectedIndex;

        private static ObservableCollection<string> _myMesages = new ObservableCollection<string>();
        private static ObservableCollection<string> _UsersList = new ObservableCollection<string>();

        //private string _myText;

        public MainWindowsViewModel()
        {
            PropertyChanged += delegate { };//чтоб не ломалось
        }

        //property
        //public string MyText
        //{
        //    get { return _myText; }
        //    set
        //    {
        //        _myText = value;
        //        PropertyChanged(this, new PropertyChangedEventArgs("MyText"));
        //    }
        //}

        public string Login { get; set; }
        public string Password { get; set; }
        public int selectedIndex
        {
            get
            {
                return _selectedIndex;
            }
            set
            {
                _selectedIndex = value;
            }
        }
        public string To_Send { get; set; }

        public ObservableCollection<string> MyMessages { get { return _myMesages; } }
        public ObservableCollection<string> __UsersList { get { return _UsersList; } }

        public ICommand MyCommand
        {
            get
            {
                if (_myCommand == null)
                {
                    _myCommand = new ActionCommand(Do);
                }

                return _myCommand;
            }
        }

        public ICommand Login_command
        {
            get
            {
                if (_Login_command == null)
                {
                    _Login_command = new ActionCommand(login_action);
                }

                return _Login_command;
            }
        }

        public ICommand Show_users
        {
            get
            {
                if(_show_users == null)
                {
                    _show_users = new ActionCommand(show_users);
                }

                return _show_users;
            }
        }

        //method
        private void Do()
        {
            //_myMesages.Add(MessengerInterop.selected_id.ToString());
            _myMesages.Add("you to " + _UsersList[MessengerInterop.selected_id]+":"+To_Send);
            MessengerInterop.send_text_message(_UsersList[MessengerInterop.selected_id],To_Send);
        }

        private void login_action()
        {
            MessengerInterop.make_client(Login, Password);
            App.Current.MainWindow.Visibility = System.Windows.Visibility.Hidden;
            var usr = new UsersList();
            usr.ShowDialog();
            App.Current.MainWindow.Visibility = System.Windows.Visibility.Visible;
            //UsersListThread.Start();
        }

        private void show_users()
        {
            if (!flag)
            {
                flag = true;
                _UsersList.Clear();
                string[] arr = new string[200];
                MessengerInterop.get_users(arr);
                int i = 0;
                while (arr[i] != null)
                {
                    _UsersList.Add(arr[i++]);
                }
            }else
            {
                //App.Current.MainWindow.Visibility = System.Windows.Visibility.Hidden;
                MessengerInterop.selected_id = _selectedIndex;
                //_UsersList.Add(_selectedIndex.ToString());
                var texting = new Texting();
                UserListThread.Start();
                //App.Current.MainWindow.Visibility = System.Windows.Visibility.Visible;
            }
            
        }

        static void task()
        {
            _myMesages.Add("test");
            Thread.Sleep(100);
        }

        Thread UserListThread = new Thread(task);

        //
        public event PropertyChangedEventHandler PropertyChanged;
    }
}

public class ActionCommand : ICommand
{
    private Action _action;

    public ActionCommand(Action action)
    {
        _action = action;
    }

    public event EventHandler CanExecuteChanged;

    public bool CanExecute(object parameter)
    {
        return true;
    }

    public void Execute(object parameter)
    {
        _action();
    }
}

public static class MessengerInterop
{
    public static int selected_id;

    [DllImport("G:\\clouds\\GitHub\\kaspersky\\development\\messenger_test\\messenger_test\\Debug\\messenger_test.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
    public static extern void make_client([MarshalAs(UnmanagedType.LPStr)] string login,
                                          [MarshalAs(UnmanagedType.LPStr)] string password);

    [DllImport("G:\\clouds\\GitHub\\kaspersky\\development\\messenger_test\\messenger_test\\Debug\\messenger_test.dll")]
    public static extern void delete_client();

    [DllImport("G:\\clouds\\GitHub\\kaspersky\\development\\messenger_test\\messenger_test\\Debug\\messenger_test.dll")]
    public static extern void send_text_message([MarshalAs(UnmanagedType.LPStr)] string recpt,
                                                [MarshalAs(UnmanagedType.LPStr)] string text_content);

    [DllImport("G:\\clouds\\GitHub\\kaspersky\\development\\messenger_test\\messenger_test\\Debug\\messenger_test.dll")]
    public static extern string receive_text_message();

    [DllImport("G:\\clouds\\GitHub\\kaspersky\\development\\messenger_test\\messenger_test\\Debug\\messenger_test.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern void get_users([In, Out][MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPStr)] string[] arr);
}