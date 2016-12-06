<?php
class inputController extends Controller {
    public function __construct() {
        parent::__construct();
        $this->_modelGas = $this->loadModel('index');
        $this->_modelClient = $this->loadModel('clients');
    }
    
    public function index() {
        $this->_view->assign('title', 'Ввод');
        $this->_view->assign('gas', $this->_modelGas->getGas());
        
        if ($this->getInt('buy_form') == 1) {
            $this->_view->assign('data', $_POST);
            
            if (!$this->getSql('payment_method')) {
                $this->_view->assign('_error', 'Выберите "Подсчет по".');
                $this->_view->renderizer('index');
                exit;
            }
            
            if (!$this->getSql('gas_type')) {
                $this->_view->assign('_error', 'Выберите "Тип топлива".');
                $this->_view->renderizer('index');
                exit;
            }
            
            if (!$this->getDecimal('input_pay')) {
                $this->_view->assign('_error', 'Введите значение поля "Ввод".');
                $this->_view->renderizer('index');
                exit;
            }
            
            $price = (float) $this->_modelGas->getGasPriceByType($this->getSql('gas_type'));
            
            $liters = round((float) $this->getDecimal('input_pay'), 2);
            
            if ($this->getSql('payment_method') == 'money') {
                $liters /= $price;
                $liters = round($liters, 2);
                $message = 'Вы заправились на ' . $liters . ' л.';
            } else {
                $pay = round($liters * $price, 2);
                $message = 'К оплате: ' . $pay . ' грн.';
            }
            
            if ($this->getInt('client_id')) {
                if (!$this->_modelClient->getClientById($this->getInt('client_id'))) {
                    $this->_view->assign('_error', 'Нет такого пользователя.');
                    $this->_view->renderizer('index');
                    exit;
                }
                
                $scores = $this->_modelClient->getScores($this->getInt('client_id'));
                $scores += $liters;
                
                $add_scores = $this->_modelClient->addScores($scores, $this->getInt('client_id'));
                
                $message .= $add_scores ? ' Начислено ' . $liters . ' б. Всего ' . $scores . ' б.' : '';
            }
                
            $this->_view->assign('_access', $message);
            $this->_view->renderizer('index');
            exit;
        }
        $this->_view->renderizer('index');
    }
}
