using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Proiect_SI
{
    public partial class MainPage : Form
    {
        private string connStr = "server=localhost;user=root;database=proiect_si;port=3306;password=root;pooling=true";
        public MainPage()
        {
            InitializeComponent();
        }

        private void MainPage_Load(object sender, EventArgs e)
        {
            this.MaximizeBox = false;
            this.FormBorderStyle= FormBorderStyle.FixedDialog;
            using (MySqlConnection conn = new MySqlConnection(connStr))
            {
                string query = "CALL select_n('30')";
                MySqlCommand cmd = new MySqlCommand(query, conn);
                conn.Open();
                MySqlDataAdapter adapter = new MySqlDataAdapter(cmd);
                DataTable dt = new DataTable();
                adapter.Fill(dt);
                dgvData.DataSource = dt;
            }
        }

        private void btnActualizare_Click(object sender, EventArgs e)
        {
            using (MySqlConnection conn = new MySqlConnection(connStr))
            {
                string query = "CALL select_n('30')";
                MySqlCommand cmd = new MySqlCommand(query, conn);
                conn.Open();
                MySqlDataAdapter adapter = new MySqlDataAdapter(cmd);
                DataTable dt = new DataTable();
                adapter.Fill(dt);
                dgvData.DataSource = dt;
            }
        }

        private void btnGrafice_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form f = new Grafice();
            f.ShowDialog();
            this.Close();
        }
    }
}
