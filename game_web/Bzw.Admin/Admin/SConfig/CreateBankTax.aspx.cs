using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;

 
    public partial class Admin_SConfig_CreateBankTax : AdminBasePage
    {
        public string BankTax;
        protected void Page_Load(object sender, EventArgs e)
        {
            	AdminPopedom.IsHoldModel( "15" );

		DataTable sd = new DataTable();
		string sql = "select * from Web_Config where id=1";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0) {
            BankTax = sd.Rows[0]["CreateBankTax"].ToString();
        }
        sd.Clear();
        }

        protected void EditPric(object sender, EventArgs e)
        {
            string strBankTax = CommonManager.Web.RequestForm("BankTax", "");
            if (!CommonManager.String.IsInteger(strBankTax))
                strBankTax = "0";
            DbSession.Default.FromSql("update Web_Config set CreateBankTax="+strBankTax).Execute();

            Alert("温馨提示：\\n\\n设置成功！", "CreateBankTax.aspx");
        }
    }
 
