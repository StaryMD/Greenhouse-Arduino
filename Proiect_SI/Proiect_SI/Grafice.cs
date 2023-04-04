using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Proiect_SI
{
    public partial class Grafice : Form
    {
        private string connStr = "server=localhost;user=root;database=proiect_si;port=3306;password=root;pooling=true";
        private int n = 100;
        private Timer timer1;
        
        public Grafice()
        {
            InitializeComponent();
        }
        private void generareGrafice(object sender, EventArgs e)
        {
            chrtSE.Series["Temperatura"].Points.Clear();
            chrtSE.Series["Umiditatea"].Points.Clear();
            chrtSI.Series["Temperatura"].Points.Clear();
            chrtSI.Series["Umiditatea"].Points.Clear();

            using (MySqlConnection conn = new MySqlConnection(connStr))
            {
                string query = "CALL select_senzor_exterior('" + n.ToString() + "')";
                MySqlCommand cmd = new MySqlCommand(query, conn);
                conn.Open();
                MySqlDataReader rdr = cmd.ExecuteReader();
                while (rdr.Read())
                {
                    chrtSE.Series["Temperatura"].Points.AddY(rdr.GetFloat("temperatura"));
                    chrtSE.Series["Umiditatea"].Points.AddY(rdr.GetFloat("umiditatea"));
                }
            }

            using (MySqlConnection conn = new MySqlConnection(connStr))
            {
                string query = "CALL select_senzor_interior('" + n.ToString() + "')";
                MySqlCommand cmd = new MySqlCommand(query, conn);
                conn.Open();
                MySqlDataReader rdr = cmd.ExecuteReader();
                while (rdr.Read())
                {
                    chrtSI.Series["Temperatura"].Points.AddY(rdr.GetFloat("temperatura"));
                    chrtSI.Series["Umiditatea"].Points.AddY(rdr.GetFloat("umiditatea"));
                }
            }
        }
        public void InitTimer()
        {
            timer1 = new Timer();
            timer1.Tick += new EventHandler(generareGrafice);
            timer1.Interval = 1000; 
            timer1.Start();
        }
        private void Grafice_Load(object sender, EventArgs e)
        {
            this.MaximizeBox = false;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.InitTimer();
        }

        private void btnInapoi_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form f = new MainPage();
            f.ShowDialog();
            this.Close();
        }

        private void btnStergere_Click(object sender, EventArgs e)
        {
            using (MySqlConnection conn = new MySqlConnection(connStr))
            {
                string query = "CALL delete_old()";
                MySqlCommand cmd = new MySqlCommand(query, conn);
                conn.Open();
                MySqlDataReader rdr = cmd.ExecuteReader();
            }
        }
    }
}
