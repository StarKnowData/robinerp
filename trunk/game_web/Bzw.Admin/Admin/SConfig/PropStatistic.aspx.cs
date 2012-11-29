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


public partial class Admin_SConfig_PropStatistic : AdminBasePage
{

    public int Rowid = 0;

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "15" );

        if (!IsPostBack)
        {
            BindList();
        }
	}

    public void BindList()
    {
        string where = string.Empty;

        int counts;
        DataTable dt = new BLL.Member().PagerListPropTotal(WebPager1.PageSize, WebPager1.CurrentPageIndex, out counts);
        WebPager1.RecordCount = counts;
        Rowid = WebPager1.CurrentPageIndex * WebPager1.PageSize - WebPager1.PageSize;
        if (dt.Rows.Count <= 0)
        {
            this.NoDataList.Visible = true;
        }
        else
        {
            rpList.DataSource = dt.DefaultView;
            rpList.DataBind();
        }
    }

    protected void WebPager1_PageChanging(object src, Wuqi.Webdiyer.PageChangingEventArgs e)
    {
        WebPager1.CurrentPageIndex = e.NewPageIndex;
        BindList();
    }

}
