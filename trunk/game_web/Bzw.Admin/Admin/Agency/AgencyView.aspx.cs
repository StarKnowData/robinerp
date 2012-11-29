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


public partial class Admin_Agency_AgencyView :AdminBasePage
{
    //protected int PageIndex
    //{
    //    get
    //    {
    //        string tmp = CommonManager.Web.Request( "page", "" );
    //        if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
    //            return 1;
    //        return int.Parse( tmp );
    //    }
    //}

	protected void Page_Load( object sender, EventArgs e )
	{
        AdminPopedom.IsHoldModel("17");

        //结算门票
		Balance();
        //设置代理帐号状态
        SetAgencyState();
        //删除
        Delete();


        databind();
	}
	public void databind()
	{
        StringBuilder where = new StringBuilder();

        string key = CommonManager.Web.RequestUrlDecode("key", "");
        string tn = CommonManager.Web.RequestUrlDecode("tn", "");


        //搜索登录帐号
        if (!string.IsNullOrEmpty(key))
            where.AppendFormat(" and AgencyName='{0}' ", key);

        ////代理ID
        //if (!string.IsNullOrEmpty(uid) && CommonManager.String.IsInteger(uid))
        //{
        //    where.AppendFormat(" and AgencyID={0} ", uid);
        //}
        //else if (!string.IsNullOrEmpty(uid))
        //{
        //    where.AppendFormat(" and AgencyID={0} ", "0");
        //}

        //真实姓名
        if (!string.IsNullOrEmpty(tn))
            where.AppendFormat(" and TrueName='{0}' ", tn);


        //获取数据
        int counts;
        DataTable dt = Utility.SqlHelper.ExecuteDataPager("Web_VGetAgencyDetail1", "AgencyID", "*", "AgencyID", 1, WebPager1.PageSize, PageIndex, out counts, where.ToString());
        WebPager1.RecordCount = counts;
        WebPager1.CurrentPageIndex = PageIndex;

        if (dt.Rows.Count <= 0)
        {
            rpList.Visible = false;
            NoDataList.Visible = true;
        }
        else
        {
            rpList.Visible = true;
            NoDataList.Visible = false;
            rpList.DataSource = dt.DefaultView;
            rpList.DataBind();
        }
	}

	public void Balance()
	{
		string action = Utility.Common.GetStringOfUrl( "action" );
        string id = Utility.Common.GetStringOfUrl("id");
        if (action == "balance" && CommonManager.String.IsInteger(id))
		{
            //判断权限
            AdminPopedom.IsHoldModel("17");

            int balance = new BLL.Agency().BalanceSingle(id, AdminInfo["ID"].ToString());
			if( balance >= 0 )
			{
				 
				Utility.Common.OutMsgBox( "结算成功，共结算了" + UiCommon.StringConfig.MoneyChu100( balance ) + "金币到ID为[" + id + "]的代理商帐号中！", Utility.Common.UrlValue );
				databind();

			}
			else
			{
				Utility.Common.OutMsgBox( "结算失败！", Utility.Common.UrlValue );
			}
		}
	}


    public void SetAgencyState()
    {
        string act = Utility.Common.GetStringOfUrl("action");
        string id = Utility.Common.GetStringOfUrl("id");
        string isTaboo = Utility.Common.GetStringOfUrl("istaboo");
        if (act.ToLower() == "zhstate" && CommonManager.String.IsInteger(id) && CommonManager.String.IsInteger(isTaboo))
        {
            //判断是否有权限
            AdminPopedom.IsHoldModel("17");

            if (Convert.ToInt32(isTaboo.Trim()) == 0)
            {
                isTaboo = "1";
            }
            else
            {
                isTaboo = "0";
            }

            new BLL.Agency().UpdateIsTaboo(id, isTaboo);
          
            CommonManager.Web.ResponseEnd(CommonManager.Web.RequestUrlDecode("url", "AgencyView.aspx"), true);
        }
    }


    public void Delete()
    {
        string act = Utility.Common.GetStringOfUrl("action");
        string id = Utility.Common.GetStringOfUrl("id");
        if (act.ToLower() == "del" && CommonManager.String.IsInteger(id))
        {
            //判断是否有权限
            AdminPopedom.IsHoldModel("17");

            new BLL.Agency().Delete(id);
     
            CommonManager.Web.ResponseEnd(CommonManager.Web.RequestUrlDecode("url", "AgencyView.aspx"), true);
        }
    }


    protected void btnBatch_Click(object sender, EventArgs e)
    {
        ////判断权限
        //AdminPopedom.IsHoldModelNo("DL_DEL");

        //if (Request["hdfSelected"] != null)
        //{
        //    IAgency agency = new Agency();
        //    string strwhere = "OR AgencyID In" + "(" + Request.Params["hdfSelected"].ToString() + ")";
        //    try
        //    {
        //        agency.DeleteAgencyDayReport(SQLHelper.SQLHelper.DeleteAgencyDayReport + strwhere);
        //        databind();
        //        this.ClientScript.RegisterClientScriptBlock(this.GetType(), new Random().Next().ToString(), SystemOperation.OpenDialog(SystemInfomation.DELETE_DATA_SUCESS));
        //    }
        //    catch (Exception ex)
        //    {
        //        this.ClientScript.RegisterClientScriptBlock(this.GetType(), new Random().Next().ToString(), SystemOperation.OpenDialog(ex.Message));
        //    }
        //}
    }
}
