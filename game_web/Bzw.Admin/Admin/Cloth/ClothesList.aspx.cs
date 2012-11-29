using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;

 
    public partial class Admin_Cloth_ClothesList :  AdminBasePage
    {
        public int TableID;
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("15");

            DataTable dt = DbSession.Default.FromSql("  SELECT * FROM dbo.Web_Clothes WHERE  LogID>0 order by LogID ").ToDataTable();
            if (dt.Rows.Count > 0)
            {
                rptClothesList.DataSource = dt;
                rptClothesList.DataBind();
            }
            dt.Clear();
        }
    }
 
