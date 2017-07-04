using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabPW8_9_b_
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
         
        }

        private void b_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void c_TextChanged(object sender, EventArgs e)
        {
         
        }

        private void button1_Click(object sender, EventArgs e)
        {
            float a = float.Parse(TextBox1.Text);
            float b = float.Parse(TextBox2.Text);
            float c = float.Parse(TextBox3.Text);
            var d = b * b - 4 * a * c;
            if (d < 0)
            {
                MessageBox.Show("Дискриминант меньше 0. Корней нет!");
            }
            if (d == 0)
            {
                MessageBox.Show("Дискриминант равен 0");
            }
            var x1 = (-b + Math.Sqrt(d)) / (2 * a);
            var x2 = (-b - Math.Sqrt(d)) / (2 * a);
            TextBox4.Text = Convert.ToString(d);
            TextBox5.Text = Convert.ToString(x1);
            TextBox6.Text = Convert.ToString(x2);
        }
    }
    }
    

