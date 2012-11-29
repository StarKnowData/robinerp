using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using BCST.Common;
using Bzw.Data;
using System.Data;

 
    public partial class Admin_SConfig_AlmsConfig :AdminBasePage
    {
       
 protected string moneyName;
        protected void Page_Load(object sender, EventArgs e)
        {
            AdminPopedom.IsHoldModel("12");
            if (!IsPostBack)
            {
                DataTable sd = DbSession.Default.FromSql("select top 1 * from Web_AlmsConfig ").ToDataTable();

                if (sd.Rows.Count > 0)
                {
                    DataRow dr = sd.Rows[0];

                    txtAlmsMoney.Text = dr["AlmsMoney"].ToString();
                    txtAlmsDayCounts.Text = dr["AlmsDayCounts"].ToString();
                    fckFirstNews.Value = dr["AlmsFirstNews"].ToString();
                    fckSecondNews.Value = dr["AlmsSecondNews"].ToString();
                    fckThirdNews.Value = dr["AlmsThirdNews"].ToString();
                    txtLimitMoney.Text = dr["AlmsLimitMoney"].ToString();
                }
                sd.Clear();
            }
        }

        protected void PrCsEdit(object sender, EventArgs e)
        {
            string strMoney = txtAlmsMoney.Text.Trim();
            if (!CommonManager.String.IsInteger(strMoney) || Convert.ToInt32(strMoney) < 0)
            {
                CommonManager.Web.RegJs(this.Page, "alert('救济金请输入大于或等于0的整数！');", true);
                return;
            }
            if (!CommonManager.String.IsInteger(txtLimitMoney.Text.Trim()) || Convert.ToInt32(txtLimitMoney.Text.Trim()) < 0)
            {
                CommonManager.Web.RegJs(this.Page, "alert('救济金底线数请输入大于或等于0的整数！');", true);
                return;
            }
            if (!CommonManager.String.IsInteger(txtAlmsDayCounts.Text.Trim()) || Convert.ToInt32(txtAlmsDayCounts.Text.Trim()) < 0)
            {
                CommonManager.Web.RegJs(this.Page, "alert('领取救济金次数请输入大于或等于0的整数！');", true);
                return;
            }
            int SqlState = DbSession.Default.FromSql("update Web_AlmsConfig set AlmsMoney=@AlmsMoney,AlmsDayCounts=@AlmsDayCounts,AlmsFirstNews=@AlmsFirstNews,AlmsSecondNews=@AlmsSecondNews,AlmsThirdNews=@AlmsThirdNews,AlmsLimitMoney=@AlmsLimitMoney where Id=1")
                .AddInputParameter("@AlmsMoney", DbType.Int32,txtAlmsMoney.Text.Trim())
                .AddInputParameter("@AlmsDayCounts",DbType.Int32,txtAlmsDayCounts.Text.Trim())
                .AddInputParameter("@AlmsFirstNews",DbType.String,fckFirstNews.Value)
                .AddInputParameter("@AlmsSecondNews", DbType.String, fckSecondNews.Value)
                .AddInputParameter("@AlmsThirdNews",DbType.String,fckThirdNews.Value)
                .AddInputParameter("@AlmsLimitMoney",DbType.String,txtLimitMoney.Text.Trim())
                .Execute();

            if (SqlState > 0)
                CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n设置成功！');", true);
            else
                CommonManager.Web.RegJs(this, "alert('温馨提示：\\n\\n设置失败！！');", true);
        }
    }
 
