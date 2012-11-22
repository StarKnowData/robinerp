/**
 * jLook 0.2
 * Nice form templates
 * by Sebastian Romano / seba@envero.org 
 *
 */
// global variables
var separator = '-'; // string que separa las cosas que se usan como id y valor
var counter = 1;
var z_actual = 100;
var lastCheckbox = '';

// plugin
jQuery.fn.jLook = function(options){
	var self = this;
	//
	$(this).addClass('jLookForm');
	// each form
	this.each(function(){
		// form link
		var actualForm = this;
		// labels
		$('label', this).addClass("jLookLabel");
		// inputs
		$('input:text', this).addClass("jLookInput");	

		// inputs
		$('input:text', this).each(function(){
			$(this).wrap('<div class="jLookInputWrapper"></div>');
			$(this).parent().css("width", $(this).css("width"));
			// foco
			$(this).focus(function(){
				$(this).addClass("jLookInput_hover");
				$(this).parent().addClass("jLookInputWrapper_hover");
			});
			// sale de foco
			$(this).blur(function(){
				$(this).removeClass("jLookInput_hover");
				$(this).parent().removeClass("jLookInputWrapper_hover");
			});
		});
		
		
		//----------------------------------------------------------
		// radio/s
		var lastRadio = '';
		$('input:radio', this).each(function(){
			// link
			$(this).before('<a href="#" id="'+$(this).attr("name")+'-'+$(this).attr("value")+'" class="jLookRadio"></a>');
			$(this).remove();
			// hidden necesary fields
			if(lastRadio != $(this).attr("name")){
				$(actualForm).prepend('<input type="hidden" id="'+$(this).attr("name")+'" name="'+$(this).attr("name")+'" value="null" />');
				lastRadio = $(this).attr("name");
			}
		});
		// click event
		$('.jLookRadio').bind('click', radioClick)

		//----------------------------------------------------------
		// checkbox/s
		$('input:checkbox', this).each(function(){
			// link
			$(this).before('<a href="#" id="'+$(this).attr("name") + separator + $(this).attr("value")+'" class="jLookCheckbox"></a>');
			$(this).remove();
			// necesary hidden fields
			if(lastCheckbox != $(this).attr("name")){
				$(actualForm).prepend('<input type="hidden" id="'+$(this).attr("name")+'" name="'+$(this).attr("name")+'" value="null" />');
				lastCheckbox = $(this).attr("name");
			}
		});
		// click event
		$('.jLookCheckbox').bind('click', checkboxClick);
		
		
		//---------------------------------
		// select/s
		$('select', this).each(function(){
			// nombre del contenedor
			var nam = $(this).attr('name')+'_wrapper';
			// contenedor
			$(this).wrap('<div class="jLookSelectWrapper" id="' + nam + '"></div>');
			// nombre del elemento
			var name = $(this).attr('name');
			// id seleccionado
			var indiceSeleccionado = this.selectedIndex;
			var selectContentHeader= '<input type="hidden" value="" name="' + name + '" id="' + name + '" /><div class="jLookSelectHeader"><div></div><a href="#" class="jLookSelectOpen"></a></div>'; // xhtml replace
			var selectContent = '<ul>';
			// veo si está el parámetro
			if(options.selectHeight) var selectContent = '<ul style="overflow:auto; height:' + options.selectHeight + 'px">';
			var index = 0; // índice seleccionado
			// recorre las opciones
			$('option', this).each(function(){
			    // armo el ul
				selectContent += '<li><a href="#" class="jLookSelectOption" id="' +  name + separator + $(this).attr('value') + '">' + $(this).html() + ' </a></li>';
				// si alguno está seleccionado lo coloco como valor
				if(indiceSeleccionado == index){
					selectContentHeader = '<input type="hidden" value="' + $(this).attr('value') + '" name="' + name + '" id="' + name + '" /><div class="jLookSelectHeader"><div>' + $(this).html() + '</div><a href="#" class="jLookSelectOpen"></a></div>'; // xhtml replace	
				}
				$(this).remove();
				index = index + 1;
			});
			selectContent += '</ul>';
			$('#' + nam).html(selectContentHeader + selectContent);
		});
		// display select options
		$('.jLookSelectOpen').bind('click', selectClick);
		// select option
		$('.jLookSelectOption').bind('click', optionClick);
		
		
		//--------------------------------------
		//textareas
		$('textarea', this).each(function(){
			$(this).wrap("<div class='jLookTextareaWrapper'></div>");
		});
	});
}


/**
 * Función encargada del control del checkbox
 */

checkboxClick = function(){
	// despligo id y value
	valu = $(this).attr("id").split(separator);
	if($('#'+valu[0]).attr("value") == valu[1]){
		$(this).removeClass('jLookCheckbox_checked'); // uncheck
		$('#'+valu[0]).attr("value", 'null');
	}else{
		$(this).addClass("jLookCheckbox_checked");
		$('#'+valu[0]).attr("value", valu[1]); // selectedValue
	}
	return false;
}

/**
 * Función encargada del control del radio
 */

radioClick = function(){
	// despliego id y value
	valu = $(this).attr("id").split('-');
	//alert($('#' + valu[0]).attr("value"));
	// si el valor nuevo es distino del viejo actualizo
	actualValue = $('#' + valu[0]).attr("value");
	if( actualValue != valu[1]){
		// quito la clase del que estaba antes seleccionado
		$('#' + valu[0] + '-' + actualValue).removeClass('jLookRadio_checked');
		// actualizo valor
		$('#' + valu[0]).attr("value", valu[1]);
		$(this).addClass('jLookRadio_checked');
	}
	// retorna nada
	return false;
}

/**
 * Click para desplegar un select
 */

selectClick = function(){
	z_actual = z_actual + 10;
	// id del contenedor
	wrapperId = $(this).parent().parent().attr('id');
	// veo si está abiero
	if($('#' + wrapperId).is('.jLookSelectOpened')){
		// lo vuelvo al estado cerrado
		$('#' + wrapperId).removeClass('jLookSelectOpened');
		// cierro
		$('ul', $('#' + wrapperId)).slideUp('slow', function(){
			// vuelvo todo a posiciones relativas
			$('.jLookSelectWrapper').each(function(){
				if($(this).attr('id') != wrapperId){
					$(this).css('position', 'relative');
				}
			});	
		});
	}else{ // expando
		// cambio las posiciones de los otros selects
		$('.jLookSelectWrapper').each(function(){
			if($(this).attr('id') != wrapperId){
				$(this).css('position', 'static');
			}
		});
		$('#' + wrapperId).addClass('jLookSelectOpened');
		$('ul', $('#' + wrapperId)).slideDown();
	}
	
	return false;
};

/**
 * Al hacer click en la opción de un select
 */
optionClick = function(){
    // cargo el valor seleccionado 
    valu = $(this).attr('id').split(separator);
    var wrapperId = valu[0] + '_wrapper';
    $('#' + valu[0]).attr('value', valu[1]);
    // muestro el valor seleccionado
    $('div', $('#' + valu[0] + '_wrapper .jLookSelectHeader')).html($(this).html());
    // cierro el select
	
	// lo vuelvo al estado cerrado
	$('#' + wrapperId).removeClass('jLookSelectOpened');
	// cierro
	$('ul', $('#' + wrapperId)).slideUp('slow', function(){
		// vuelvo todo a posiciones relativas
		$('.jLookSelectWrapper').each(function(){
			if($(this).attr('id') != wrapperId){
				$(this).css('position', 'relative');
			}
		});	
	});
	return false;
};

/**
 * Esta función obtiene el campo que el elemento
 * tiene que llenar y lo llena (ya que manejo algunas cosas con hiddens)
 */

setHidden = function(id, value){
	
}
