import React from 'react';
import { Provider } from '../../utils';
import ProviderItem from './ProviderItem';
import styled from 'styled-components';
const PROVIDERS: Provider[] = [
  {
    id: '1',
    name: 'MatHem',
    logo:
      'http://resources.mynewsdesk.com/image/upload/c_limit,dpr_2.0,f_auto,h_700,q_auto,w_690/o10uwyrabub2ala6mibj.jpg'
  },
  {
    id: '2',
    name: 'Linas Matkasse',
    logo:
      'https://storesupport.se/wp-content/uploads/2016/09/linas-matkasse-logo.png'
  },
  {
    id: '3',
    name: 'Coop',
    logo:
      'https://pressrum.coop.se/download.php?file=/2016/10/Coop-Logotyp-250x73.jpg'
  }
];

const ProviderInfo = styled.div``;

const ProviderList = () => {
  return (
    <div>
      <ProviderInfo>
        <h2>Integrations</h2>
        Connect to 3:rd party integrations to easily add your available
        ingredients
      </ProviderInfo>
      {PROVIDERS.map(provider => {
        return <ProviderItem key={provider.id} provider={provider} />;
      })}
    </div>
  );
};

export default ProviderList;
