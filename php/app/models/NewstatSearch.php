<?php

namespace app\models;

use Yii;
use yii\base\Model;
use yii\data\ActiveDataProvider;
use app\models\Newstat;

/**
 * NewstatSearch represents the model behind the search form of `app\models\Newstat`.
 */
class NewstatSearch extends Newstat
{
    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['machine_id', 'online'], 'safe'],
        ];
    }

    /**
     * @inheritdoc
     */
    public function scenarios()
    {
        // bypass scenarios() implementation in the parent class
        return Model::scenarios();
    }

    /**
     * Creates data provider instance with search query applied
     *
     * @param array $params
     *
     * @return ActiveDataProvider
     */
    public function search($params)
    {
        $query = Newstat::find();

        // add conditions that should always apply here

        $dataProvider = new ActiveDataProvider([
            'query' => $query,
            'pagination' => [
                'pageSize' => 50,
            ],
        ]);

        $this->load($params);

        if (!$this->validate()) {
            // uncomment the following line if you do not want to return any records when validation fails
            // $query->where('0=1');
            return $dataProvider;
        }

        // grid filtering conditions
        // $query->andFilterWhere([
        //     'activetime' => $this->activetime,
        // ]);

        $query->andFilterWhere(['like', 'machine_id', $this->machine_id])
            ->andFilterWhere(['online' => $this->online]);

        $query->addOrderBy(['activetime' => SORT_DESC]);
        return $dataProvider;
    }
}
