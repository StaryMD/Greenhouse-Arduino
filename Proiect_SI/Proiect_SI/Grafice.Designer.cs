namespace Proiect_SI
{
    partial class Grafice
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnInapoi = new System.Windows.Forms.Button();
            this.chrtSE = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.chrtSI = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.btnStergere = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.chrtSE)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chrtSI)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold);
            this.label1.Location = new System.Drawing.Point(331, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(212, 31);
            this.label1.TabIndex = 1;
            this.label1.Text = "Senzor exterior";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold);
            this.label2.Location = new System.Drawing.Point(338, 264);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(205, 31);
            this.label2.TabIndex = 1;
            this.label2.Text = "Senzor interior";
            // 
            // btnInapoi
            // 
            this.btnInapoi.Location = new System.Drawing.Point(66, 472);
            this.btnInapoi.Name = "btnInapoi";
            this.btnInapoi.Size = new System.Drawing.Size(115, 41);
            this.btnInapoi.TabIndex = 3;
            this.btnInapoi.Text = "<< Inapoi";
            this.btnInapoi.UseVisualStyleBackColor = true;
            this.btnInapoi.Click += new System.EventHandler(this.btnInapoi_Click);
            // 
            // chrtSE
            // 
            chartArea1.Name = "ChartArea1";
            this.chrtSE.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.chrtSE.Legends.Add(legend1);
            this.chrtSE.Location = new System.Drawing.Point(50, 84);
            this.chrtSE.Name = "chrtSE";
            this.chrtSE.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            this.chrtSE.PaletteCustomColors = new System.Drawing.Color[] {
        System.Drawing.Color.Red,
        System.Drawing.Color.Blue};
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.Legend = "Legend1";
            series1.Name = "Temperatura";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series2.Legend = "Legend1";
            series2.Name = "Umiditatea";
            this.chrtSE.Series.Add(series1);
            this.chrtSE.Series.Add(series2);
            this.chrtSE.Size = new System.Drawing.Size(771, 159);
            this.chrtSE.TabIndex = 5;
            this.chrtSE.Text = "chart1";
            // 
            // chrtSI
            // 
            chartArea2.Name = "ChartArea1";
            this.chrtSI.ChartAreas.Add(chartArea2);
            legend2.Name = "Legend1";
            this.chrtSI.Legends.Add(legend2);
            this.chrtSI.Location = new System.Drawing.Point(50, 298);
            this.chrtSI.Name = "chrtSI";
            this.chrtSI.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            this.chrtSI.PaletteCustomColors = new System.Drawing.Color[] {
        System.Drawing.Color.Red,
        System.Drawing.Color.Blue};
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series3.Legend = "Legend1";
            series3.Name = "Temperatura";
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series4.Legend = "Legend1";
            series4.Name = "Umiditatea";
            this.chrtSI.Series.Add(series3);
            this.chrtSI.Series.Add(series4);
            this.chrtSI.Size = new System.Drawing.Size(771, 159);
            this.chrtSI.TabIndex = 6;
            this.chrtSI.Text = "chart1";
            // 
            // btnStergere
            // 
            this.btnStergere.Location = new System.Drawing.Point(685, 472);
            this.btnStergere.Name = "btnStergere";
            this.btnStergere.Size = new System.Drawing.Size(115, 41);
            this.btnStergere.TabIndex = 7;
            this.btnStergere.Text = "Sterge datele";
            this.btnStergere.UseVisualStyleBackColor = true;
            this.btnStergere.Click += new System.EventHandler(this.btnStergere_Click);
            // 
            // Grafice
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(884, 541);
            this.Controls.Add(this.btnStergere);
            this.Controls.Add(this.chrtSI);
            this.Controls.Add(this.chrtSE);
            this.Controls.Add(this.btnInapoi);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Grafice";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Grafice";
            this.Load += new System.EventHandler(this.Grafice_Load);
            ((System.ComponentModel.ISupportInitialize)(this.chrtSE)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chrtSI)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnInapoi;
        private System.Windows.Forms.DataVisualization.Charting.Chart chrtSE;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chrtSI;
        private System.Windows.Forms.Button btnStergere;
    }
}