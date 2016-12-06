 <?php
  function pp($arr){ /*pretty print*/
      $retStr = '<ul>';
      if (is_array($arr)){
          foreach ($arr as $key=>$val){
              if (is_array($val)){
                  $retStr .= '<li>' . $key . ' => ' . pp($val) . '</li>';
              }else{
                  $retStr .= '<li>' . $key . ' => ' . $val . '</li>';
              }
          }
      }
      $retStr .= '</ul>';
      return $retStr;
  } 
  ?>
