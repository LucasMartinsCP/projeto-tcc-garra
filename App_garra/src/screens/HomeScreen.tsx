import { View, Text, Button } from 'react-native';

export default function HomeScreen({ navigation }: { navigation: any }) {
  return (
    <View style={{ flex: 1, justifyContent: 'center', alignItems: 'center' }}>
      <Text>Controle da Máquina de Garra</Text>
      <Button title="Ir para Joystick" onPress={() => navigation.navigate('Joystick')} />
    </View>
  );
}