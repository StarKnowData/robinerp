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
using BCST.Common;
using Bzw.Data;
namespace Bzw.Inhersits.Manage
{
    public partial class Manage_MyRoom : UiCommon.ManageBasePage
    {
        /// <summary>
        /// Head1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

        /// <summary>
        /// webmeta1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webmeta1;

        /// <summary>
        /// webTopOne 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webTopOne;

        /// <summary>
        /// leftOne 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl leftOne;

        /// <summary>
        /// webServiceOne 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webServiceOne;

        /// <summary>
        /// rpList 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rpList;

        /// <summary>
        /// anpPageIndex 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::Wuqi.Webdiyer.AspNetPager anpPageIndex;

        /// <summary>
        /// webFooterone 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webFooterone;
        //序号
        public int Rowid = 0;

        protected int PageIndex
        {
            get
            {
                string pi = CommonManager.Web.Request("page", "");
                if (string.IsNullOrEmpty(pi) || !CommonManager.String.IsInteger(pi))
                    return 1;
                return int.Parse(pi);
            }
        }



        protected void Page_Load(object sender, EventArgs e)
        {
            BindLogList();

        }

        public void BindLogList()
        {
            string where = " and UserID='" + UiCommon.UserLoginInfo.UserID + "'";
            int counts = 0;
            DataTable dt = Utility.SqlHelper.ExecuteDataPager("Web_VApplyVipRoom", "ID", "*", "AddDate", 1, anpPageIndex.PageSize, anpPageIndex.CurrentPageIndex, out counts, where);
            DataColumn col = new DataColumn();
            col.ColumnName = "TaxCom";
            dt.Columns.Add(col);
            if (dt.Rows.Count > 0)
            {
                foreach (DataRow row1 in dt.Rows)
                {
                    if (Convert.ToDateTime(row1["OpenRoomDate"].ToString())  < DateTime.Now)
                    {
                        row1["TaxCom"] = DbSession.Default.FromSql("select ISNULL(SUM(ChangeTax),0)  FROM VChangeRecord WHERE RoomID in (select roomid from tgameroomInfo where tenancyID=" + row1["ID"].ToString() + ") and EndTime<'" + DateTime.Now.ToString("yyyy-MM-dd 00:00:00") + "' ").ToScalar();

                    }
                }
                anpPageIndex.RecordCount = counts;
                rpList.DataSource = dt.DefaultView;
                rpList.DataBind();
            }
            else
            {
                CommonManager.Web.RegJs(this, "alert('您还没有租赁房间记录，请先租赁房间！');location.href='/Manage/ApplyVipRoom.aspx'" , true);
            }
        }
    }
}
