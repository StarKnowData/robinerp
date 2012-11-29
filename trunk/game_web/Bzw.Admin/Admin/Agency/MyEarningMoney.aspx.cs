using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Data.SqlClient;

using System.Text;
using BCST.Common;
using Bzw.Data;

public partial class Admin_Agency_MyEarningMoney : AdminBasePage
{
    public string SumMoneyTotal = "0.00";
    public string MySumMoneyTotal = "0.00";
    public string PayMoneyTotal = "0.00";
    public string MyMoneyTotal = "0.00";

    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("17");

        dtpFrom.Attributes.Add("onclick", "WdatePicker()");
        dtpFrom.Attributes.Add("onfocus", "WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\\'dtpTo\\')}'});");
        dtpTo.Attributes.Add("onclick", "WdatePicker()");
        dtpTo.Attributes.Add("onfocus", "WdatePicker({dateFmt:'yyyy-MM-dd',minDate:'#F{$dp.$D(\\'dtpFrom\\')}'});");

        if (!IsPostBack)
        {
            databind();
        }
    }

    public void databind()
    {
        string id = Utility.Common.GetStringOfUrl("id");
        if (!Utility.Common.IsNumber(id))
        {
            return;
        }

        StringBuilder where = new StringBuilder(" where AgencyID=" + id + " ");

        int cntFlg = 0;
        //===
        string startTM = dtpFrom.Text.Trim();
        if (startTM.Length > 0 && CommonManager.String.IsDateTime(startTM))
        {
            where.AppendFormat(" and CountTime > '{0} 00:00:00' ", startTM);
            cntFlg += 1;
        }

        //===
        string endTM = dtpTo.Text.Trim();
        if (endTM.Length > 0 && CommonManager.String.IsDateTime(endTM))
        {
            endTM = Convert.ToDateTime(endTM.Trim()).AddDays(1).ToString("yyyy-MM-dd");//多加一天
            where.AppendFormat(" and CountTime <= '{0} 00:00:00' ", endTM);
            cntFlg += 1;
        }

        //Response.Write(where.ToString());

        StringBuilder cmdText = new StringBuilder();
        cmdText.Append(" select ");
        cmdText.Append("b.ComName,");
        cmdText.Append("SumMoney=sum(SpareMoney),"); //门票贡献
        cmdText.Append("MySumMoney=sum(SpareMoney*MyPercent/100),"); //应得佣金
        cmdText.Append("PayMoney=sum(SpareMoney*MyPercent/100-ActualSpareMoney),"); //应付佣金
        cmdText.Append("MyMoney=sum(ActualSpareMoney) "); //收益
        cmdText.Append(" from Web_AgencyDayReport a inner join TGameNameInfo b ");
        cmdText.Append(" on a.GameNameID=b.NameID ");
        cmdText.Append(" " + where.ToString() + " group by a.GameNameID,b.ComName ");

        DataTable dt = null;
        if (cntFlg == 2)
        {
            dt = DbSession.Default.FromSql(cmdText.ToString()).ToDataTable();
        }

        if (dt != null && dt.Rows.Count > 0)
        {
            rptDataList.DataSource = dt;
            rptDataList.DataBind();
            rptDataList.Visible = true;
            ltNonData.Visible = false;

            SumMoneyTotal = UiCommon.StringConfig.MoneyChu100(dt.Compute("sum(SumMoney)", ""));
            MySumMoneyTotal = UiCommon.StringConfig.MoneyChu100(dt.Compute("sum(MySumMoney)", ""));
            PayMoneyTotal = UiCommon.StringConfig.MoneyChu100(dt.Compute("sum(PayMoney)", ""));
            MyMoneyTotal = UiCommon.StringConfig.MoneyChu100(dt.Compute("sum(MyMoney)", ""));
        }
        else
        {
            rptDataList.Visible = false;
            ltNonData.Visible = true;
        }
    }

    protected void btnSearch_Click(object sender, EventArgs e)
    {
        databind();
    }

    public string GetStartTM()
    {
        string startTM = dtpFrom.Text.Trim();
        if (startTM.Length > 0 && CommonManager.String.IsDateTime(startTM))
        {
            return startTM + " 00:00:00";
        }
        else
        {
            return DateTime.Now.ToString("yyyy-MM-dd") + " 00:00:00";
        }
    }

    public string GetEndTM()
    {
        string endTM = dtpTo.Text.Trim();
        if (endTM.Length > 0 && CommonManager.String.IsDateTime(endTM))
        {
            return endTM + " 23:59:59";
        }
        else
        {
            return DateTime.Now.ToString("yyyy-MM-dd") + " 23:59:59";
        }
    }

    /*
    public void databind()
    {
        string id = Utility.Common.GetStringOfUrl("id");
        if (!Utility.Common.IsNumber(id))
        {
            return;
        }

        StringBuilder where = new StringBuilder(" where AgencyID=" + id + " ");

        int cntFlg = 0;
        //===
        string startTM = dtpFrom.Text.Trim();
        if (startTM.Length > 0 && CommonManager.String.IsDateTime(startTM))
        {
            where.AppendFormat(" and CountTime>='{0} 00:00:00' ", startTM);
            cntFlg += 1;
        }

        //===
        string endTM = dtpTo.Text.Trim();
        if (endTM.Length > 0 && CommonManager.String.IsDateTime(endTM))
        {
            where.AppendFormat(" and CountTime<='{0} 23:59:59' ", endTM);
            cntFlg += 1;
        }

        StringBuilder cmdText = new StringBuilder();
        cmdText.Append(" select ");
        cmdText.Append("b.ComName,");
        cmdText.Append("SumMoney=sum(SpareMoney),"); //门票贡献
        cmdText.Append("MySumMoney=sum(SpareMoney*MyPercent/100),"); //应得佣金
        cmdText.Append("PayMoney=sum(SpareMoney*MyPercent/100-ActualSpareMoney),"); //应付佣金
        cmdText.Append("MyMoney=sum(ActualSpareMoney) "); //收益
        cmdText.Append(" from Web_AgencyDayReport a inner join TGameNameInfo b ");
        cmdText.Append(" on a.GameNameID=b.NameID ");
        cmdText.Append(" " + where.ToString() + " group by a.GameNameID,b.ComName ");

        DataTable dt = null;
        if (cntFlg == 2)
        {
           dt = DbSession.Default.FromSql(cmdText.ToString()).ToDataTable();
        }

        if (dt !=null && dt.Rows.Count > 0)
        {
            rptDataList.DataSource = dt;
            rptDataList.DataBind();
            rptDataList.Visible = true;
            ltNonData.Visible = false;

            SumMoneyTotal = UiCommon.StringConfig.MoneyChu100(dt.Compute("sum(SumMoney)",""));
            MySumMoneyTotal = UiCommon.StringConfig.MoneyChu100(dt.Compute("sum(MySumMoney)", ""));
            PayMoneyTotal = UiCommon.StringConfig.MoneyChu100(dt.Compute("sum(PayMoney)", ""));
            MyMoneyTotal = UiCommon.StringConfig.MoneyChu100(dt.Compute("sum(MyMoney)", ""));
        }
        else
        {
            rptDataList.Visible = false;
            ltNonData.Visible = true;
        }
    }

    protected void btnSearch_Click(object sender, EventArgs e)
    {
        databind();
    }

    public string GetStartTM()
    {
        string startTM = dtpFrom.Text.Trim();
        if (startTM.Length > 0 && CommonManager.String.IsDateTime(startTM))
        {
            return startTM + " 00:00:00";
        }
        else
        {
            return DateTime.Now.ToString("yyyy-MM-dd") + " 00:00:00";
        }
    }

    public string GetEndTM()
    {
        string endTM = dtpTo.Text.Trim();
        if (endTM.Length > 0 && CommonManager.String.IsDateTime(endTM))
        {
            return endTM + " 23:59:59";
        }
        else
        {
            return DateTime.Now.ToString("yyyy-MM-dd") + " 23:59:59";
        }
    }*/
}
