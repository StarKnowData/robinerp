
//打开一个浮动页
function openRoomRuleDiv(page, width, height) {
    Msg("<iframe src=" + page + " frameborder=\"0\" height=" + height + " width=" + (width - 50) + " ></iframe>", width);

}

//在浮动页内关闭浮动页
function setValue() {
    window.parent.document.myform.RoomRule.value = getTheValue();
    $(window.parent.document).find("#Mask").hide();
    $(window.parent.document).find("#Mask").remove();
    $(window.parent.document).find("#Tranning").hide();
    $(window.parent.document).find("#Tranning").remove();


}

//浮动页返回值给父页
function getTheValue() {
    var temp = 0;
    for (i = 0; i < document.form1.elements.length; i++) {
        var e = document.form1.elements[i];
        if (e.checked) {
            temp = temp + parseInt(e.value);
        }
    }
    return temp;
}

