﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GUI
{
    /// <summary>
    /// Логика взаимодействия для Texting.xaml
    /// </summary>
    public partial class Texting : Window
    {
        public Texting()
        {
            InitializeComponent();

            this.DataContext = new MainWindowsViewModel {};
        }
    }
}
